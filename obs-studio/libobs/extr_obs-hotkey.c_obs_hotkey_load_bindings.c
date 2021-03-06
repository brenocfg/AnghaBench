#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_key_combination_t ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;
struct TYPE_4__ {int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_1__ hotkeys; } ;
struct TYPE_6__ {TYPE_2__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_binding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ find_id (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  hotkey_signal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock () ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  remove_bindings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_load_bindings(obs_hotkey_id id,
			      obs_key_combination_t *combinations, size_t num)
{
	size_t idx;

	if (!lock())
		return;

	if (find_id(id, &idx)) {
		obs_hotkey_t *hotkey = &obs->hotkeys.hotkeys.array[idx];
		remove_bindings(id);
		for (size_t i = 0; i < num; i++)
			create_binding(hotkey, combinations[i]);

		hotkey_signal("hotkey_bindings_changed", hotkey);
	}
	unlock();
}