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
struct ux500_dma_channel {scalar_t__ is_allocated; int /*<<< orphan*/  ch_num; TYPE_1__* controller; } ;
struct musb {int /*<<< orphan*/  controller; } ;
struct dma_channel {scalar_t__ actual_len; int /*<<< orphan*/  status; struct ux500_dma_channel* private_data; } ;
struct TYPE_2__ {struct musb* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DMA_STATUS_FREE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ux500_dma_channel_release(struct dma_channel *channel)
{
	struct ux500_dma_channel *ux500_channel = channel->private_data;
	struct musb *musb = ux500_channel->controller->private_data;

	dev_dbg(musb->controller, "channel=%d\n", ux500_channel->ch_num);

	if (ux500_channel->is_allocated) {
		ux500_channel->is_allocated = 0;
		channel->status = MUSB_DMA_STATUS_FREE;
		channel->actual_len = 0;
	}
}