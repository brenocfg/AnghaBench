#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_query_hotkeys_helper {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  strict_modifiers; int /*<<< orphan*/  thread_disable_press; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERACT_ALT_KEY ; 
 int /*<<< orphan*/  INTERACT_COMMAND_KEY ; 
 int /*<<< orphan*/  INTERACT_CONTROL_KEY ; 
 int /*<<< orphan*/  INTERACT_SHIFT_KEY ; 
 int /*<<< orphan*/  OBS_KEY_ALT ; 
 int /*<<< orphan*/  OBS_KEY_CONTROL ; 
 int /*<<< orphan*/  OBS_KEY_META ; 
 int /*<<< orphan*/  OBS_KEY_SHIFT ; 
 int /*<<< orphan*/  enum_bindings (int /*<<< orphan*/ ,struct obs_query_hotkeys_helper*) ; 
 scalar_t__ is_pressed (int /*<<< orphan*/ ) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  query_hotkey ; 

__attribute__((used)) static inline void query_hotkeys()
{
	uint32_t modifiers = 0;
	if (is_pressed(OBS_KEY_SHIFT))
		modifiers |= INTERACT_SHIFT_KEY;
	if (is_pressed(OBS_KEY_CONTROL))
		modifiers |= INTERACT_CONTROL_KEY;
	if (is_pressed(OBS_KEY_ALT))
		modifiers |= INTERACT_ALT_KEY;
	if (is_pressed(OBS_KEY_META))
		modifiers |= INTERACT_COMMAND_KEY;

	struct obs_query_hotkeys_helper param = {
		modifiers,
		obs->hotkeys.thread_disable_press,
		obs->hotkeys.strict_modifiers,
	};
	enum_bindings(query_hotkey, &param);
}