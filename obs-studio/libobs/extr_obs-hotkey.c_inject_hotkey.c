#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ key; int /*<<< orphan*/  modifiers; } ;
struct obs_hotkey_internal_inject {int /*<<< orphan*/  strict_modifiers; TYPE_2__ hotkey; int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {scalar_t__ key; } ;
struct TYPE_9__ {TYPE_1__ key; } ;
typedef  TYPE_3__ obs_hotkey_binding_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  handle_binding (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ modifiers_match (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool inject_hotkey(void *data, size_t idx,
				 obs_hotkey_binding_t *binding)
{
	UNUSED_PARAMETER(idx);
	struct obs_hotkey_internal_inject *event = data;

	if (modifiers_match(binding, event->hotkey.modifiers,
			    event->strict_modifiers)) {
		bool pressed = binding->key.key == event->hotkey.key &&
			       event->pressed;
		handle_binding(binding, event->hotkey.modifiers, false,
			       event->strict_modifiers, &pressed);
	}

	return true;
}