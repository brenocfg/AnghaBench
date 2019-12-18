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
struct obs_query_hotkeys_helper {int /*<<< orphan*/  strict_modifiers; int /*<<< orphan*/  no_press; int /*<<< orphan*/  modifiers; } ;
typedef  int /*<<< orphan*/  obs_hotkey_binding_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  handle_binding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool query_hotkey(void *data, size_t idx,
				obs_hotkey_binding_t *binding)
{
	UNUSED_PARAMETER(idx);

	struct obs_query_hotkeys_helper *param =
		(struct obs_query_hotkeys_helper *)data;
	handle_binding(binding, param->modifiers, param->no_press,
		       param->strict_modifiers, NULL);

	return true;
}