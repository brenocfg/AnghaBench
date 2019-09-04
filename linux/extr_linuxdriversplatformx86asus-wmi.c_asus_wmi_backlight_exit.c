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
struct asus_wmi {int /*<<< orphan*/ * backlight_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_wmi_backlight_exit(struct asus_wmi *asus)
{
	backlight_device_unregister(asus->backlight_device);

	asus->backlight_device = NULL;
}