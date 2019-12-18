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
 int /*<<< orphan*/  lock () ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/ * save_hotkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock () ; 

obs_data_array_t *obs_hotkey_save(obs_hotkey_id id)
{
	size_t idx;
	obs_data_array_t *result = NULL;

	if (!lock())
		return result;

	if (find_id(id, &idx))
		result = save_hotkey(&obs->hotkeys.hotkeys.array[idx]);
	unlock();

	return result;
}