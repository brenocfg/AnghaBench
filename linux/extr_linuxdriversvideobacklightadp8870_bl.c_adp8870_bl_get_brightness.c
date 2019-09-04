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
struct backlight_device {int dummy; } ;
struct adp8870_bl {int current_brightness; } ;

/* Variables and functions */
 struct adp8870_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp8870_bl_get_brightness(struct backlight_device *bl)
{
	struct adp8870_bl *data = bl_get_data(bl);

	return data->current_brightness;
}