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
struct hv_device {struct vmbus_channel* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmbus_close (struct vmbus_channel*) ; 

__attribute__((used)) static int hvs_remove(struct hv_device *hdev)
{
	struct vmbus_channel *chan = hdev->channel;

	vmbus_close(chan);

	return 0;
}