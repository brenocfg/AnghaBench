#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_4__ obs_hotkey_pair_t ;
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
struct TYPE_7__ {int /*<<< orphan*/ * array; } ;
struct TYPE_6__ {TYPE_4__* array; } ;
struct TYPE_8__ {TYPE_2__ hotkeys; TYPE_1__ hotkey_pairs; } ;
struct TYPE_10__ {TYPE_3__ hotkeys; } ;

/* Variables and functions */
 scalar_t__ find_id (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  find_pair_id (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  lock () ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/ * save_hotkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_pair_save(obs_hotkey_pair_id id, obs_data_array_t **p_data0,
			  obs_data_array_t **p_data1)
{
	if ((!p_data0 && !p_data1) || !lock())
		return;

	size_t idx;
	if (!find_pair_id(id, &idx))
		goto unlock;

	obs_hotkey_pair_t *pair = &obs->hotkeys.hotkey_pairs.array[idx];

	if (p_data0 && find_id(pair->id[0], &idx)) {
		*p_data0 = save_hotkey(&obs->hotkeys.hotkeys.array[idx]);
	}
	if (p_data1 && find_id(pair->id[1], &idx)) {
		*p_data1 = save_hotkey(&obs->hotkeys.hotkeys.array[idx]);
	}

unlock:
	unlock();
}