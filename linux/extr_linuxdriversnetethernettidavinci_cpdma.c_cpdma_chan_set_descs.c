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
struct cpdma_ctlr {struct cpdma_chan** channels; } ;
struct cpdma_chan {int weight; int desc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPDMA_MAX_CHANNELS ; 
 int rx_chan_num (int /*<<< orphan*/ ) ; 
 int tx_chan_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpdma_chan_set_descs(struct cpdma_ctlr *ctlr,
				 int rx, int desc_num,
				 int per_ch_desc)
{
	struct cpdma_chan *chan, *most_chan = NULL;
	int desc_cnt = desc_num;
	int most_dnum = 0;
	int min, max, i;

	if (!desc_num)
		return;

	if (rx) {
		min = rx_chan_num(0);
		max = rx_chan_num(CPDMA_MAX_CHANNELS);
	} else {
		min = tx_chan_num(0);
		max = tx_chan_num(CPDMA_MAX_CHANNELS);
	}

	for (i = min; i < max; i++) {
		chan = ctlr->channels[i];
		if (!chan)
			continue;

		if (chan->weight)
			chan->desc_num = (chan->weight * desc_num) / 100;
		else
			chan->desc_num = per_ch_desc;

		desc_cnt -= chan->desc_num;

		if (most_dnum < chan->desc_num) {
			most_dnum = chan->desc_num;
			most_chan = chan;
		}
	}
	/* use remains */
	if (most_chan)
		most_chan->desc_num += desc_cnt;
}