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
typedef  int /*<<< orphan*/  obs_hotkey_id ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
struct TYPE_4__ {int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_1__ hotkeys; } ;
struct TYPE_6__ {TYPE_2__ hotkeys; } ;

/* Variables and functions */
 scalar_t__ find_id (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  load_bindings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock () ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  remove_bindings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_load(obs_hotkey_id id, obs_data_array_t *data)
{
	size_t idx;

	if (!lock())
		return;

	if (find_id(id, &idx)) {
		remove_bindings(id);
		load_bindings(&obs->hotkeys.hotkeys.array[idx], data);
	}
	unlock();
}