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
struct lp8788_bl {struct backlight_device* bl_dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 

__attribute__((used)) static void lp8788_backlight_unregister(struct lp8788_bl *bl)
{
	struct backlight_device *bl_dev = bl->bl_dev;

	backlight_device_unregister(bl_dev);
}