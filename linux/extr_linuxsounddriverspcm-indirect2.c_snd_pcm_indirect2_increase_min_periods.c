#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_indirect2 {scalar_t__ min_periods; scalar_t__ sw_io; scalar_t__ sw_buffer_size; int check_alignment; int bytes2hw; unsigned int sw_data; unsigned int min_period_count; int hw_buffer_size; } ;

/* Variables and functions */
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static void
snd_pcm_indirect2_increase_min_periods(struct snd_pcm_substream *substream,
				       struct snd_pcm_indirect2 *rec,
				       int isplay, int iscopy,
				       unsigned int bytes)
{
	if (rec->min_periods >= 0) {
		if (iscopy) {
			rec->sw_io += bytes;
			if (rec->sw_io >= rec->sw_buffer_size)
				rec->sw_io -= rec->sw_buffer_size;
		} else if (isplay) {
			/* If application does not write data in multiples of
			 * a period, move sw_data to the next correctly aligned
			 * position, so that sw_io can converge to it (in the
			 * next step).
			 */
			if (!rec->check_alignment) {
				if (rec->bytes2hw %
				    snd_pcm_lib_period_bytes(substream)) {
					unsigned bytes2hw_aligned =
					    (1 +
					     (rec->bytes2hw /
					      snd_pcm_lib_period_bytes
					      (substream))) *
					    snd_pcm_lib_period_bytes
					    (substream);
					rec->sw_data =
					    bytes2hw_aligned %
					    rec->sw_buffer_size;
#ifdef SND_PCM_INDIRECT2_STAT
					snd_printk(KERN_DEBUG
						   "STAT: @re-align: aligned "
						   "bytes2hw to next period "
						   "size boundary: %d "
						   "(instead of %d)\n",
						   bytes2hw_aligned,
						   rec->bytes2hw);
					snd_printk(KERN_DEBUG
						   "STAT: @re-align: sw_data "
						   "moves to: %d\n",
						   rec->sw_data);
#endif
				}
				rec->check_alignment = 1;
			}
			/* We are at the end and are copying zeros into the
			 * fifo.
			 * Now, we have to make sure that sw_io is increased
			 * until the position of sw_data: Filling the fifo with
			 * the first zeros means, the last bytes were played.
			 */
			if (rec->sw_io != rec->sw_data) {
				unsigned int diff;
				if (rec->sw_data > rec->sw_io)
					diff = rec->sw_data - rec->sw_io;
				else
					diff = (rec->sw_buffer_size -
						rec->sw_io) +
						rec->sw_data;
				if (bytes >= diff)
					rec->sw_io = rec->sw_data;
				else {
					rec->sw_io += bytes;
					if (rec->sw_io >= rec->sw_buffer_size)
						rec->sw_io -=
						    rec->sw_buffer_size;
				}
			}
		}
		rec->min_period_count += bytes;
		if (rec->min_period_count >= (rec->hw_buffer_size / 2)) {
			rec->min_periods += (rec->min_period_count /
					     (rec->hw_buffer_size / 2));
#ifdef SND_PCM_INDIRECT2_STAT
			if ((rec->min_period_count /
			     (rec->hw_buffer_size / 2)) > 7)
				snd_printk(KERN_DEBUG
					   "STAT: more than 7 (%d) min_adds "
					   "at once - too big to save!\n",
					   (rec->min_period_count /
					    (rec->hw_buffer_size / 2)));
			else
				rec->min_adds[(rec->min_period_count /
					       (rec->hw_buffer_size / 2))]++;
#endif
			rec->min_period_count = (rec->min_period_count %
						 (rec->hw_buffer_size / 2));
		}
	} else if (isplay && iscopy)
		rec->min_periods = 0;
}