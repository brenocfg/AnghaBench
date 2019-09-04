#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int gpio; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct brcms_info {TYPE_1__ radio_led; TYPE_2__ led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_2__*) ; 

void brcms_led_unregister(struct brcms_info *wl)
{
	if (wl->led_dev.dev)
		led_classdev_unregister(&wl->led_dev);
	if (wl->radio_led.gpio != -1)
		gpio_free(wl->radio_led.gpio);
}