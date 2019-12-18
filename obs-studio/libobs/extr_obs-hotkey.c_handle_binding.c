#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ key; int /*<<< orphan*/  modifiers; } ;
struct TYPE_8__ {int modifiers_match; scalar_t__ pressed; TYPE_1__ key; } ;
typedef  TYPE_2__ obs_hotkey_binding_t ;

/* Variables and functions */
 scalar_t__ OBS_KEY_NONE ; 
 int /*<<< orphan*/  is_pressed (scalar_t__) ; 
 int modifiers_match (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  press_released_binding (TYPE_2__*) ; 
 int /*<<< orphan*/  release_pressed_binding (TYPE_2__*) ; 

__attribute__((used)) static inline void handle_binding(obs_hotkey_binding_t *binding,
				  uint32_t modifiers, bool no_press,
				  bool strict_modifiers, bool *pressed)
{
	bool modifiers_match_ =
		modifiers_match(binding, modifiers, strict_modifiers);
	bool modifiers_only = binding->key.key == OBS_KEY_NONE;

	if (!binding->key.modifiers)
		binding->modifiers_match = true;

	if (modifiers_only)
		pressed = &modifiers_only;

	if (!binding->key.modifiers && modifiers_only)
		goto reset;

	if ((!binding->modifiers_match && !modifiers_only) || !modifiers_match_)
		goto reset;

	if ((pressed && !*pressed) ||
	    (!pressed && !is_pressed(binding->key.key)))
		goto reset;

	if (binding->pressed || no_press)
		return;

	press_released_binding(binding);
	return;

reset:
	binding->modifiers_match = modifiers_match_;
	if (!binding->pressed)
		return;

	release_pressed_binding(binding);
}