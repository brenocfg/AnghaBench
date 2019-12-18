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
struct obs_core_hotkeys {int /*<<< orphan*/ * platform_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 

void obs_hotkeys_platform_free(struct obs_core_hotkeys *hotkeys)
{
	bfree(hotkeys->platform_context);
	hotkeys->platform_context = NULL;
}