#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct save_bindings_helper_t {int /*<<< orphan*/  array; TYPE_1__* hotkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  modifiers; } ;
struct TYPE_7__ {scalar_t__ hotkey_id; TYPE_2__ key; } ;
typedef  TYPE_3__ obs_hotkey_binding_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_5__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERACT_ALT_KEY ; 
 int /*<<< orphan*/  INTERACT_COMMAND_KEY ; 
 int /*<<< orphan*/  INTERACT_CONTROL_KEY ; 
 int /*<<< orphan*/  INTERACT_SHIFT_KEY ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  obs_data_array_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_key_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_modifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool save_bindings_helper(void *data, size_t idx,
					obs_hotkey_binding_t *binding)
{
	UNUSED_PARAMETER(idx);
	struct save_bindings_helper_t *h = data;

	if (h->hotkey->id != binding->hotkey_id)
		return true;

	obs_data_t *hotkey = obs_data_create();

	uint32_t modifiers = binding->key.modifiers;
	save_modifier(modifiers, hotkey, "shift", INTERACT_SHIFT_KEY);
	save_modifier(modifiers, hotkey, "control", INTERACT_CONTROL_KEY);
	save_modifier(modifiers, hotkey, "alt", INTERACT_ALT_KEY);
	save_modifier(modifiers, hotkey, "command", INTERACT_COMMAND_KEY);

	obs_data_set_string(hotkey, "key", obs_key_to_name(binding->key.key));

	obs_data_array_push_back(h->array, hotkey);

	obs_data_release(hotkey);

	return true;
}