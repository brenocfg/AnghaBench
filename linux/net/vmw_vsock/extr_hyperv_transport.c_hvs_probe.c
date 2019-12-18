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
struct vmbus_channel {int dummy; } ;
struct hv_vmbus_device_id {int dummy; } ;
struct hv_device {struct vmbus_channel* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvs_open_connection (struct vmbus_channel*) ; 

__attribute__((used)) static int hvs_probe(struct hv_device *hdev,
		     const struct hv_vmbus_device_id *dev_id)
{
	struct vmbus_channel *chan = hdev->channel;

	hvs_open_connection(chan);

	/* Always return success to suppress the unnecessary error message
	 * in vmbus_probe(): on error the host will rescind the device in
	 * 30 seconds and we can do cleanup at that time in
	 * vmbus_onoffer_rescind().
	 */
	return 0;
}