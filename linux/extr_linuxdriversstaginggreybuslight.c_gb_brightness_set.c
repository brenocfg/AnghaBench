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
struct led_classdev {int dummy; } ;
struct gb_channel {TYPE_1__* led; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int brightness; } ;

/* Variables and functions */
 int __gb_lights_brightness_set (struct gb_channel*) ; 
 struct gb_channel* get_channel_from_cdev (struct led_classdev*) ; 

__attribute__((used)) static int gb_brightness_set(struct led_classdev *cdev,
			     enum led_brightness value)
{
	struct gb_channel *channel = get_channel_from_cdev(cdev);

	channel->led->brightness = value;

	return __gb_lights_brightness_set(channel);
}