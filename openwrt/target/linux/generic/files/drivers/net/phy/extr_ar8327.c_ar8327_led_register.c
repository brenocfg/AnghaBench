#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct ar8327_led {scalar_t__ mode; TYPE_1__ cdev; } ;

/* Variables and functions */
 scalar_t__ AR8327_LED_MODE_HW ; 
 int /*<<< orphan*/  dev_attr_enable_hw_mode ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static int
ar8327_led_register(struct ar8327_led *aled)
{
	int ret;

	ret = led_classdev_register(NULL, &aled->cdev);
	if (ret < 0)
		return ret;

	if (aled->mode == AR8327_LED_MODE_HW) {
		ret = device_create_file(aled->cdev.dev,
					 &dev_attr_enable_hw_mode);
		if (ret)
			goto err_unregister;
	}

	return 0;

err_unregister:
	led_classdev_unregister(&aled->cdev);
	return ret;
}