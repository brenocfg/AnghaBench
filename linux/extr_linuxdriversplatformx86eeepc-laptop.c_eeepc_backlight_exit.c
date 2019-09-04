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
struct eeepc_laptop {int /*<<< orphan*/ * backlight_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeepc_backlight_exit(struct eeepc_laptop *eeepc)
{
	backlight_device_unregister(eeepc->backlight_device);
	eeepc->backlight_device = NULL;
}