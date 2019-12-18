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
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct obs_context_data {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  fixup_pointers () ; 
 scalar_t__ unregister_hotkey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_release_hotkeys(struct obs_context_data *context)
{
	if (!context->hotkeys.num)
		goto cleanup;

	bool need_fixup = false;
	for (size_t i = 0; i < context->hotkeys.num; i++)
		need_fixup = unregister_hotkey(context->hotkeys.array[i]) ||
			     need_fixup;

	if (need_fixup)
		fixup_pointers();

cleanup:
	da_free(context->hotkeys);
}