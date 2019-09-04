#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_core_hotkeys {TYPE_2__* platform_context; } ;
struct TYPE_5__ {struct TYPE_5__* keysyms; int /*<<< orphan*/  display; TYPE_1__* keycodes; } ;
typedef  TYPE_2__ obs_hotkeys_platform_t ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

void obs_hotkeys_platform_free(struct obs_core_hotkeys *hotkeys)
{
	obs_hotkeys_platform_t *context = hotkeys->platform_context;

	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++)
		da_free(context->keycodes[i].list);

	XCloseDisplay(context->display);
	bfree(context->keysyms);
	bfree(context);

	hotkeys->platform_context = NULL;
}