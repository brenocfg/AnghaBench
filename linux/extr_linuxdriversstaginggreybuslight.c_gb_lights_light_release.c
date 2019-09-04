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
struct gb_light {int ready; int channels_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * channels; scalar_t__ has_flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_lights_channel_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_lights_light_v4l2_unregister (struct gb_light*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_lights_light_release(struct gb_light *light)
{
	int i;
	int count;

	light->ready = false;

	count = light->channels_count;

	if (light->has_flash)
		gb_lights_light_v4l2_unregister(light);

	for (i = 0; i < count; i++) {
		gb_lights_channel_release(&light->channels[i]);
		light->channels_count--;
	}
	kfree(light->channels);
	kfree(light->name);
}