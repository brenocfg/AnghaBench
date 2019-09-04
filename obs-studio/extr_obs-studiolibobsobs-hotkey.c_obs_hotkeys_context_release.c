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
struct obs_context_data {int /*<<< orphan*/  hotkey_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_release_hotkey_pairs (struct obs_context_data*) ; 
 int /*<<< orphan*/  context_release_hotkeys (struct obs_context_data*) ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkeys_context_release(struct obs_context_data *context)
{
	if (!lock())
		return;

	context_release_hotkeys(context);
	context_release_hotkey_pairs(context);

	obs_data_release(context->hotkey_data);
	unlock();
}