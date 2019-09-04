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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct asus_wmi {int /*<<< orphan*/  kbd_led_work; int /*<<< orphan*/  led_workqueue; TYPE_1__ kbd_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_hotk_resume(struct device *device)
{
	struct asus_wmi *asus = dev_get_drvdata(device);

	if (!IS_ERR_OR_NULL(asus->kbd_led.dev))
		queue_work(asus->led_workqueue, &asus->kbd_led_work);

	return 0;
}