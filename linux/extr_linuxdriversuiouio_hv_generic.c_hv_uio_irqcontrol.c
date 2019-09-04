#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uio_info {struct hv_uio_private_data* priv; } ;
struct hv_uio_private_data {struct hv_device* device; } ;
struct hv_device {TYPE_3__* channel; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {TYPE_1__* ring_buffer; } ;
struct TYPE_6__ {TYPE_2__ inbound; } ;
struct TYPE_4__ {int interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  virt_mb () ; 

__attribute__((used)) static int
hv_uio_irqcontrol(struct uio_info *info, s32 irq_state)
{
	struct hv_uio_private_data *pdata = info->priv;
	struct hv_device *dev = pdata->device;

	dev->channel->inbound.ring_buffer->interrupt_mask = !irq_state;
	virt_mb();

	return 0;
}