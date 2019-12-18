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
struct snd_pcxhr {int nb_streams_capt; int nb_streams_play; int /*<<< orphan*/ * playback_stream; int /*<<< orphan*/ * capture_stream; } ;
struct pcxhr_mgr {int src_it_dsp; int dsp_time_last; int granularity; int num_cards; int /*<<< orphan*/  lock; struct snd_pcxhr** chip; TYPE_1__* pci; int /*<<< orphan*/  dsp_time_err; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PCXHR_DSP_TIME_INVALID ; 
 int PCXHR_DSP_TIME_MASK ; 
 int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int PCXHR_IRQ_TIMER ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_msg_thread (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_update_timer_pos (struct pcxhr_mgr*,int /*<<< orphan*/ *,int) ; 

irqreturn_t pcxhr_threaded_irq(int irq, void *dev_id)
{
	struct pcxhr_mgr *mgr = dev_id;
	int i, j;
	struct snd_pcxhr *chip;

	mutex_lock(&mgr->lock);
	if (mgr->src_it_dsp & PCXHR_IRQ_TIMER) {
		/* is a 24 bit counter */
		int dsp_time_new =
			PCXHR_INPL(mgr, PCXHR_PLX_MBOX4) & PCXHR_DSP_TIME_MASK;
		int dsp_time_diff = dsp_time_new - mgr->dsp_time_last;

		if ((dsp_time_diff < 0) &&
		    (mgr->dsp_time_last != PCXHR_DSP_TIME_INVALID)) {
			/* handle dsp counter wraparound without resync */
			int tmp_diff = dsp_time_diff + PCXHR_DSP_TIME_MASK + 1;
			dev_dbg(&mgr->pci->dev,
				"WARNING DSP timestamp old(%d) new(%d)",
				    mgr->dsp_time_last, dsp_time_new);
			if (tmp_diff > 0 && tmp_diff <= (2*mgr->granularity)) {
				dev_dbg(&mgr->pci->dev,
					"-> timestamp wraparound OK: "
					    "diff=%d\n", tmp_diff);
				dsp_time_diff = tmp_diff;
			} else {
				dev_dbg(&mgr->pci->dev,
					"-> resynchronize all streams\n");
				mgr->dsp_time_err++;
			}
		}
#ifdef CONFIG_SND_DEBUG_VERBOSE
		if (dsp_time_diff == 0)
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME NO DIFF time(%d)\n",
				    dsp_time_new);
		else if (dsp_time_diff >= (2*mgr->granularity))
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME TOO BIG old(%d) add(%d)\n",
				    mgr->dsp_time_last,
				    dsp_time_new - mgr->dsp_time_last);
		else if (dsp_time_diff % mgr->granularity)
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME increased by %d\n",
				    dsp_time_diff);
#endif
		mgr->dsp_time_last = dsp_time_new;

		for (i = 0; i < mgr->num_cards; i++) {
			chip = mgr->chip[i];
			for (j = 0; j < chip->nb_streams_capt; j++)
				pcxhr_update_timer_pos(mgr,
						&chip->capture_stream[j],
						dsp_time_diff);
		}
		for (i = 0; i < mgr->num_cards; i++) {
			chip = mgr->chip[i];
			for (j = 0; j < chip->nb_streams_play; j++)
				pcxhr_update_timer_pos(mgr,
						&chip->playback_stream[j],
						dsp_time_diff);
		}
	}

	pcxhr_msg_thread(mgr);
	mutex_unlock(&mgr->lock);
	return IRQ_HANDLED;
}