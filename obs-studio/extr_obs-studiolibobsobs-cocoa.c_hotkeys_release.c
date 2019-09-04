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
struct obs_hotkeys_platform {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_hotkeys_platform (struct obs_hotkeys_platform*) ; 
 int os_atomic_dec_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hotkeys_release(struct obs_hotkeys_platform *plat)
{
	if (os_atomic_dec_long(&plat->refs) == -1)
		free_hotkeys_platform(plat);
}