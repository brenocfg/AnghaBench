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
struct obs_context_data {int /*<<< orphan*/  hotkeys; } ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void context_add_hotkey(struct obs_context_data *context,
				      obs_hotkey_id id)
{
	da_push_back(context->hotkeys, &id);
}