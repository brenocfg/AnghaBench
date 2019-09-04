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
struct cpdma_ctlr {int num_tx_desc; int num_rx_desc; struct cpdma_chan** channels; int /*<<< orphan*/  chan_num; } ;
struct cpdma_chan {scalar_t__ weight; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cpdma_chan**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpdma_chan_set_descs (struct cpdma_ctlr*,int,int,int) ; 
 scalar_t__ is_rx_chan (struct cpdma_chan*) ; 

int cpdma_chan_split_pool(struct cpdma_ctlr *ctlr)
{
	int tx_per_ch_desc = 0, rx_per_ch_desc = 0;
	int free_rx_num = 0, free_tx_num = 0;
	int rx_weight = 0, tx_weight = 0;
	int tx_desc_num, rx_desc_num;
	struct cpdma_chan *chan;
	int i;

	if (!ctlr->chan_num)
		return 0;

	for (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) {
		chan = ctlr->channels[i];
		if (!chan)
			continue;

		if (is_rx_chan(chan)) {
			if (!chan->weight)
				free_rx_num++;
			rx_weight += chan->weight;
		} else {
			if (!chan->weight)
				free_tx_num++;
			tx_weight += chan->weight;
		}
	}

	if (rx_weight > 100 || tx_weight > 100)
		return -EINVAL;

	tx_desc_num = ctlr->num_tx_desc;
	rx_desc_num = ctlr->num_rx_desc;

	if (free_tx_num) {
		tx_per_ch_desc = tx_desc_num - (tx_weight * tx_desc_num) / 100;
		tx_per_ch_desc /= free_tx_num;
	}
	if (free_rx_num) {
		rx_per_ch_desc = rx_desc_num - (rx_weight * rx_desc_num) / 100;
		rx_per_ch_desc /= free_rx_num;
	}

	cpdma_chan_set_descs(ctlr, 0, tx_desc_num, tx_per_ch_desc);
	cpdma_chan_set_descs(ctlr, 1, rx_desc_num, rx_per_ch_desc);

	return 0;
}