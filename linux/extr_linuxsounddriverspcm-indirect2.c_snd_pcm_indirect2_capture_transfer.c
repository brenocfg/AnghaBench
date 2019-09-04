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
struct snd_pcm_indirect2 {void* appl_ptr; int sw_ready; size_t sw_buffer_size; size_t sw_data; size_t bytes2hw; scalar_t__ hw_ready; int /*<<< orphan*/  sw_io; } ;
typedef  void* snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;
typedef  unsigned int (* snd_pcm_indirect2_zero_t ) (struct snd_pcm_substream*,struct snd_pcm_indirect2*) ;
typedef  size_t (* snd_pcm_indirect2_copy_t ) (struct snd_pcm_substream*,struct snd_pcm_indirect2*,size_t) ;
struct TYPE_2__ {void* appl_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_POS_XRUN ; 
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_pcm_indirect2_increase_min_periods (struct snd_pcm_substream*,struct snd_pcm_indirect2*,int /*<<< orphan*/ ,int,size_t) ; 

__attribute__((used)) static void
snd_pcm_indirect2_capture_transfer(struct snd_pcm_substream *substream,
				   struct snd_pcm_indirect2 *rec,
				   snd_pcm_indirect2_copy_t copy,
				   snd_pcm_indirect2_zero_t null)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t appl_ptr = runtime->control->appl_ptr;
	snd_pcm_sframes_t diff = appl_ptr - rec->appl_ptr;

	if (diff) {
#ifdef SND_PCM_INDIRECT2_STAT
		rec->lastdifftime = jiffies;
#endif
		if (diff < -(snd_pcm_sframes_t) (runtime->boundary / 2))
			diff += runtime->boundary;
		rec->sw_ready -= frames_to_bytes(runtime, diff);
		rec->appl_ptr = appl_ptr;
	}
	/* if hardware has something, but the intermediate buffer is full
	 * => skip contents of buffer
	 */
	if (rec->hw_ready && (rec->sw_ready >= (int)rec->sw_buffer_size)) {
		unsigned int bytes;

#ifdef SND_PCM_INDIRECT2_STAT
		if (rec->firstzerotime == 0) {
			rec->firstzerotime = jiffies;
			snd_printk(KERN_DEBUG "STAT: (capture) "
				   "@firstzerotime: mul_elapsed: %d, "
				   "min_period_count: %d\n",
				   rec->mul_elapsed, rec->min_period_count);
			snd_printk(KERN_DEBUG "STAT: (capture) "
				   "@firstzerotime: sw_io: %d, sw_data: %d, "
				   "appl_ptr: %u\n",
				   rec->sw_io, rec->sw_data,
				   (unsigned int)appl_ptr);
		}
		if ((jiffies - rec->firstzerotime) < 3750) {
			rec->zero_times[(jiffies - rec->firstzerotime)]++;
			rec->zero_times_saved++;
		} else
			rec->zero_times_notsaved++;
#endif
		bytes = null(substream, rec);

#ifdef SND_PCM_INDIRECT2_STAT
		rec->zeros2hw += bytes;
		if (bytes < 64)
			rec->zero_sizes[bytes]++;
		else
			snd_printk(KERN_DEBUG
				   "STAT: (capture) %d zero Bytes copied to "
				   "hardware at once - too big to save!\n",
				   bytes);
#endif
		snd_pcm_indirect2_increase_min_periods(substream, rec, 0, 0,
						       bytes);
		/* report an overrun */
		rec->sw_io = SNDRV_PCM_POS_XRUN;
		return;
	}
	while (rec->hw_ready && (rec->sw_ready < (int)rec->sw_buffer_size)) {
		/* sw_to_end: max. number of bytes that we can write to the
		 *  intermediate buffer (until it's end)
		 */
		size_t sw_to_end = rec->sw_buffer_size - rec->sw_data;

		/* bytes: max. number of bytes, which may be copied to the
		 *  intermediate buffer without overflow (in _one_ step)
		 */
		size_t bytes = rec->sw_buffer_size - rec->sw_ready;

		/* limit number of bytes (for transfer) by available room in
		 * the intermediate buffer
		 */
		if (sw_to_end < bytes)
			bytes = sw_to_end;
		if (!bytes)
			break;

#ifdef SND_PCM_INDIRECT2_STAT
		if (rec->firstbytetime == 0)
			rec->firstbytetime = jiffies;
		rec->lastbytetime = jiffies;
#endif
		/* copy bytes from the intermediate buffer (position sw_data)
		 * to the HW at most and return number of bytes actually copied
		 * from HW
		 * Furthermore, set hw_ready to 0, if the fifo is empty now.
		 */
		bytes = copy(substream, rec, bytes);
		rec->bytes2hw += bytes;

#ifdef SND_PCM_INDIRECT2_STAT
		if (bytes < 64)
			rec->byte_sizes[bytes]++;
		else
			snd_printk(KERN_DEBUG
				   "STAT: (capture) %d Bytes copied to "
				   "hardware at once - too big to save!\n",
				   bytes);
#endif
		/* increase sw_data by the number of actually copied bytes from
		 * HW
		 */
		rec->sw_data += bytes;
		if (rec->sw_data == rec->sw_buffer_size)
			rec->sw_data = 0;

		snd_pcm_indirect2_increase_min_periods(substream, rec, 0, 1,
						       bytes);

		/* number of bytes in the intermediate buffer, which haven't
		 * been fetched by ALSA yet.
		 */
		rec->sw_ready += bytes;
	}
	return;
}