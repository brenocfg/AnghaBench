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
struct led_classdev {int /*<<< orphan*/ * name; } ;
struct gb_channel {int /*<<< orphan*/ * led; int /*<<< orphan*/  is_registered; } ;

/* Variables and functions */
 struct led_classdev* get_channel_cdev (struct gb_channel*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (struct led_classdev*) ; 

__attribute__((used)) static void __gb_lights_led_unregister(struct gb_channel *channel)
{
	struct led_classdev *cdev = get_channel_cdev(channel);

	if (!channel->is_registered)
		return;

	led_classdev_unregister(cdev);
	kfree(cdev->name);
	cdev->name = NULL;
	channel->led = NULL;
}