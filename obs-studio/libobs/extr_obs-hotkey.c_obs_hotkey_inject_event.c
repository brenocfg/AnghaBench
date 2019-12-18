#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct obs_hotkey_internal_inject {int member_1; int /*<<< orphan*/  member_2; TYPE_1__ member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; int /*<<< orphan*/  modifiers; } ;
typedef  TYPE_3__ obs_key_combination_t ;
struct TYPE_7__ {int /*<<< orphan*/  strict_modifiers; } ;
struct TYPE_9__ {TYPE_2__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  enum_bindings (int /*<<< orphan*/ ,struct obs_hotkey_internal_inject*) ; 
 int /*<<< orphan*/  inject_hotkey ; 
 int /*<<< orphan*/  lock () ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_inject_event(obs_key_combination_t hotkey, bool pressed)
{
	if (!lock())
		return;

	struct obs_hotkey_internal_inject event = {
		{hotkey.modifiers, hotkey.key},
		pressed,
		obs->hotkeys.strict_modifiers,
	};
	enum_bindings(inject_hotkey, &event);
	unlock();
}