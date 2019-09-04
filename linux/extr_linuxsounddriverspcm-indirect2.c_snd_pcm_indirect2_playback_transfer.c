#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int boundary; TYPE_1__* control; } ;
struct snd_pcm_indirect2 {void* appl_ptr; int sw_ready; unsigned int sw_buffer_size; unsigned int sw_data; unsigned int bytes2hw; scalar_t__ hw_ready; } ;
typedef  void* snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;
typedef  unsigned int (* snd_pcm_indirect2_zero_t ) (struct snd_pcm_substream*,struct snd_pcm_indirect2*) ;
typedef  unsigned int (* snd_pcm_indirect2_copy_t ) (struct snd_pcm_substream*,struct snd_pcm_indirect2*,unsigned int) ;
struct TYPE_2__ {void* appl_ptr; } ;

/* Variables and functions */
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_pcm_indirect2_increase_min_periods (struct snd_pcm_substream*,struct snd_pcm_indirect2*,int,int,unsigned int) ; 

__attribute__((used)) static void
snd_pcm_indirect2_playback_transfer(struct snd_pcm_substream *substream,
				    struct snd_pcm_indirect2 *rec,
				    snd_pcm_indirect2_copy_t copy,
				    snd_pcm_indirect2_zero_t zero)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t appl_ptr = runtime->control->appl_ptr;

	/* runtime->control->appl_ptr: position where ALSA will write next time
	 * rec->appl_ptr: position where ALSA was last time
	 * diff: obviously ALSA wrote that much bytes into the intermediate
	 * buffer since we checked last time
	 */
	snd_pcm_sframes_t diff = appl_ptr - rec->appl_ptr;

	if (diff) {
#ifdef SND_PCM_INDIRECT2_STAT
		rec->lastdifftime = jiffies;
#endif
		if (diff < -(snd_pcm_sframes_t) (runtime->boundary / 2))
			diff += runtime->boundary;
		/* number of bytes "added" by ALSA increases the number of
		 * bytes which are ready to "be transferred to HW"/"played"
		 * Then, set rec->appl_ptr to not count bytes twice next time.
		 */
		rec->sw_ready += (int)frames_to_bytes(runtime, diff);
		rec->appl_ptr = appl_ptr;
	}
	if (rec->hw_ready && (rec->sw_ready <= 0)) {
		unsigned int bytes;

#ifdef SND_PCM_INDIRECT2_STAT
		if (rec->firstzerotime == 0) {
			rec->firstzerotime = jiffies;
			snd_printk(KERN_DEBUG
				   "STAT: @firstzerotime: mul_elapsed: %d, "
				   "min_period_count: %d\n",
				   rec->mul_elapsed, rec->min_period_count);
			snd_printk(KERN_DEBUG
				   "STAT: @firstzerotime: sw_io: %d, "
				   "sw_data: %d, appl_ptr: %u\n",
				   rec->sw_io, rec->sw_data,
				   (unsigned int)appl_ptr);
		}
		if ((jiffies - rec->firstzerotime) < 3750) {
			rec->zero_times[(jiffies - rec->firstzerotime)]++;
			rec->zero_times_saved++;
		} else
			rec->zero_times_notsaved++;
#endif
		bytes = zero(substream, rec);

#ifdef SND_PCM_INDIRECT2_STAT
		rec->zeros2hw += bytes;
		if (bytes < 64)
			rec->zero_sizes[bytes]++;
		else
			snd_printk(KERN_DEBUG
				   "STAT: %d zero Bytes copied to hardware at "
				   "once - too big to save!\n",
				   bytes);
#endif
		snd_pcm_indirect2_increase_min_periods(substream, rec, 1, 0,
						       bytes);
		return;
	}
	while (rec->hw_ready && (rec->sw_ready > 0)) {
		/* sw_to_end: max. number of bytes that can be read/take from
		 * the current position (sw_data) in _one_ step
		 */
		unsigned int sw_to_end = rec->sw_buffer_size - rec->sw_data;

		/* bytes: number of bytes we have available (for reading) */
		unsigned int bytes = rec->sw_ready;

		if (sw_to_end < bytes)
			bytes = sw_to_end;
		if (!bytes)
			break;

#ifdef SND_PCM_INDIRECT2_STAT
		if (rec->firstbytetime == 0)
			rec->firstbytetime = jiffies;
		rec->lastbytetime = jiffies;
#endif
		/* copy bytes from intermediate buffer position sw_data to the
		 * HW and return number of bytes actually written
		 * Furthermore, set hw_ready to 0, if the fifo isn't empty
		 * now => more could be transferred to fifo
		 */
		bytes = copy(substream, rec, bytes);
		rec->bytes2hw += bytes;

#ifdef SND_PCM_INDIRECT2_STAT
		if (bytes < 64)
			rec->byte_sizes[bytes]++;
		else
			snd_printk(KERN_DEBUG
				   "STAT: %d Bytes copied to hardware at once "
				   "- too big to save!\n",
				   bytes);
#endif
		/* increase sw_data by the number of actually written bytes
		 * (= number of taken bytes from intermediate buffer)
		 */
		rec->sw_data += bytes;
		if (rec->sw_data == rec->sw_buffer_size)
			rec->sw_data = 0;
		/* now sw_data is the position where ALSA is going to write
		 * in the intermediate buffer next time = position we are going
		 * to read from next time
		 */

		snd_pcm_indirect2_increase_min_periods(substream, rec, 1, 1,
						       bytes);

		/* we read bytes from intermediate buffer, so we need to say
		 * that the number of bytes ready for transfer are decreased
		 * now
		 */
		rec->sw_ready -= bytes;
	}
	return;
}