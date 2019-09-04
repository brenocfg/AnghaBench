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
struct hv_device {int /*<<< orphan*/  device; TYPE_1__* channel; } ;
struct completion {int dummy; } ;
struct TYPE_2__ {scalar_t__ rescind; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int) ; 

__attribute__((used)) static int wait_for_response(struct hv_device *hdev,
			     struct completion *comp)
{
	while (true) {
		if (hdev->channel->rescind) {
			dev_warn_once(&hdev->device, "The device is gone.\n");
			return -ENODEV;
		}

		if (wait_for_completion_timeout(comp, HZ / 10))
			break;
	}

	return 0;
}