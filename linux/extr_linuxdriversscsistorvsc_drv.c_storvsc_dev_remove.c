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
struct storvsc_device {int destroy; struct storvsc_device* stor_chns; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct storvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct storvsc_device*) ; 
 int /*<<< orphan*/  storvsc_wait_to_drain (struct storvsc_device*) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int storvsc_dev_remove(struct hv_device *device)
{
	struct storvsc_device *stor_device;

	stor_device = hv_get_drvdata(device);

	stor_device->destroy = true;

	/* Make sure flag is set before waiting */
	wmb();

	/*
	 * At this point, all outbound traffic should be disable. We
	 * only allow inbound traffic (responses) to proceed so that
	 * outstanding requests can be completed.
	 */

	storvsc_wait_to_drain(stor_device);

	/*
	 * Since we have already drained, we don't need to busy wait
	 * as was done in final_release_stor_device()
	 * Note that we cannot set the ext pointer to NULL until
	 * we have drained - to drain the outgoing packets, we need to
	 * allow incoming packets.
	 */
	hv_set_drvdata(device, NULL);

	/* Close the channel */
	vmbus_close(device->channel);

	kfree(stor_device->stor_chns);
	kfree(stor_device);
	return 0;
}