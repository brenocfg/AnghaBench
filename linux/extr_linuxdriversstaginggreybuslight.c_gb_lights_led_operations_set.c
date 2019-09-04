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
struct led_classdev {int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  brightness_get; } ;
struct gb_channel {int flags; } ;

/* Variables and functions */
 int GB_LIGHT_CHANNEL_BLINK ; 
 int /*<<< orphan*/  gb_blink_set ; 
 int /*<<< orphan*/  gb_brightness_get ; 
 int /*<<< orphan*/  gb_brightness_set ; 

__attribute__((used)) static void gb_lights_led_operations_set(struct gb_channel *channel,
					 struct led_classdev *cdev)
{
	cdev->brightness_get = gb_brightness_get;
	cdev->brightness_set_blocking = gb_brightness_set;

	if (channel->flags & GB_LIGHT_CHANNEL_BLINK)
		cdev->blink_set = gb_blink_set;
}