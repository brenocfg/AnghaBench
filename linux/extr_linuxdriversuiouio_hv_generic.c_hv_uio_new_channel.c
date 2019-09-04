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
struct TYPE_5__ {TYPE_1__* ring_buffer; } ;
struct vmbus_channel {int /*<<< orphan*/  kobj; TYPE_2__ inbound; TYPE_3__* primary_channel; } ;
struct device {int dummy; } ;
struct hv_device {struct device device; } ;
struct TYPE_6__ {struct hv_device* device_obj; } ;
struct TYPE_4__ {int interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_CALL_ISR ; 
 size_t HV_RING_SIZE ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  hv_uio_channel_cb ; 
 int /*<<< orphan*/  ring_buffer_bin_attr ; 
 int /*<<< orphan*/  set_channel_read_mode (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_close (struct vmbus_channel*) ; 
 int vmbus_open (struct vmbus_channel*,size_t const,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmbus_channel*) ; 

__attribute__((used)) static void
hv_uio_new_channel(struct vmbus_channel *new_sc)
{
	struct hv_device *hv_dev = new_sc->primary_channel->device_obj;
	struct device *device = &hv_dev->device;
	const size_t ring_bytes = HV_RING_SIZE * PAGE_SIZE;
	int ret;

	/* Create host communication ring */
	ret = vmbus_open(new_sc, ring_bytes, ring_bytes, NULL, 0,
			 hv_uio_channel_cb, new_sc);
	if (ret) {
		dev_err(device, "vmbus_open subchannel failed: %d\n", ret);
		return;
	}

	/* Disable interrupts on sub channel */
	new_sc->inbound.ring_buffer->interrupt_mask = 1;
	set_channel_read_mode(new_sc, HV_CALL_ISR);

	ret = sysfs_create_bin_file(&new_sc->kobj, &ring_buffer_bin_attr);
	if (ret) {
		dev_err(device, "sysfs create ring bin file failed; %d\n", ret);
		vmbus_close(new_sc);
	}
}