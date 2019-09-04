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
struct rx_ring_info {int rx_channel; } ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DMA_CTL_STAT (int) ; 
 int /*<<< orphan*/  RX_DMA_ENT_MSK (int) ; 
 int /*<<< orphan*/  RX_DMA_ENT_MSK_ALL ; 
 int /*<<< orphan*/  niu_enable_rx_channel (struct niu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_rx_channel_reset (struct niu*,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_reset_one_rx_channel(struct niu *np, struct rx_ring_info *rp)
{
	int channel = rp->rx_channel;

	(void) niu_rx_channel_reset(np, channel);
	nw64(RX_DMA_ENT_MSK(channel), RX_DMA_ENT_MSK_ALL);
	nw64(RX_DMA_CTL_STAT(channel), 0);
	(void) niu_enable_rx_channel(np, channel, 0);
}