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
struct xlgmac_hw_ops {int /*<<< orphan*/  (* enable_int ) (struct xlgmac_channel*,int) ;} ;
struct xlgmac_pdata {unsigned int channel_count; struct xlgmac_channel* channel_head; struct xlgmac_hw_ops hw_ops; } ;
struct xlgmac_channel {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;
typedef  enum xlgmac_int { ____Placeholder_xlgmac_int } xlgmac_int ;

/* Variables and functions */
 int XLGMAC_INT_DMA_CH_SR_RI ; 
 int XLGMAC_INT_DMA_CH_SR_TI ; 
 int XLGMAC_INT_DMA_CH_SR_TI_RI ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_channel*,int) ; 

__attribute__((used)) static void xlgmac_enable_rx_tx_ints(struct xlgmac_pdata *pdata)
{
	struct xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	struct xlgmac_channel *channel;
	enum xlgmac_int int_id;
	unsigned int i;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (channel->tx_ring && channel->rx_ring)
			int_id = XLGMAC_INT_DMA_CH_SR_TI_RI;
		else if (channel->tx_ring)
			int_id = XLGMAC_INT_DMA_CH_SR_TI;
		else if (channel->rx_ring)
			int_id = XLGMAC_INT_DMA_CH_SR_RI;
		else
			continue;

		hw_ops->enable_int(channel, int_id);
	}
}