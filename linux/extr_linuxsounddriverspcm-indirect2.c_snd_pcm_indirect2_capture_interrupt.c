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
struct snd_pcm_indirect2 {int hw_ready; int min_periods; int min_multiple; } ;
typedef  int /*<<< orphan*/  snd_pcm_indirect2_zero_t ;
typedef  int /*<<< orphan*/  snd_pcm_indirect2_copy_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_indirect2_capture_transfer (struct snd_pcm_substream*,struct snd_pcm_indirect2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

void
snd_pcm_indirect2_capture_interrupt(struct snd_pcm_substream *substream,
				    struct snd_pcm_indirect2 *rec,
				    snd_pcm_indirect2_copy_t copy,
				    snd_pcm_indirect2_zero_t null)
{
#ifdef SND_PCM_INDIRECT2_STAT
	rec->irq_occured++;
#endif
	/* hardware recorded some bytes, so there is something to read from the
	 * record fifo:
	 */
	rec->hw_ready = 1;

	/* don't call ack() now, instead call transfer() function directly
	 * (normally called by ack() )
	 */
	snd_pcm_indirect2_capture_transfer(substream, rec, copy, null);

	if (rec->min_periods >= rec->min_multiple) {

#ifdef SND_PCM_INDIRECT2_STAT
		if ((rec->min_periods / rec->min_multiple) > 7)
			snd_printk(KERN_DEBUG
				   "STAT: more than 7 (%d) mul_adds - "
				   "too big to save!\n",
				   (rec->min_periods / rec->min_multiple));
		else
			rec->mul_adds[(rec->min_periods /
				       rec->min_multiple)]++;
		rec->mul_elapsed_real += (rec->min_periods /
					  rec->min_multiple);
		rec->mul_elapsed++;
#endif
		rec->min_periods = (rec->min_periods % rec->min_multiple);
		snd_pcm_period_elapsed(substream);
	}
}