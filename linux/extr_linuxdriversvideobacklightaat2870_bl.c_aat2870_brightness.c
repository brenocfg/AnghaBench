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
struct TYPE_2__ {int max_brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct aat2870_bl_driver_data {int max_current; struct backlight_device* bd; } ;

/* Variables and functions */

__attribute__((used)) static inline int aat2870_brightness(struct aat2870_bl_driver_data *aat2870_bl,
				     int brightness)
{
	struct backlight_device *bd = aat2870_bl->bd;
	int val;

	val = brightness * (aat2870_bl->max_current - 1);
	val /= bd->props.max_brightness;

	return val;
}