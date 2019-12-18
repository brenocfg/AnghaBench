#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_3__ obs_hotkey_pair_t ;
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;
struct TYPE_5__ {TYPE_3__* array; } ;
struct TYPE_6__ {TYPE_1__ hotkey_pairs; } ;
struct TYPE_8__ {TYPE_2__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_pair_id (int /*<<< orphan*/ ,size_t*) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  obs_hotkey_set_name (int /*<<< orphan*/ ,char const*) ; 

void obs_hotkey_pair_set_names(obs_hotkey_pair_id id, const char *name0,
			       const char *name1)
{
	size_t idx;
	obs_hotkey_pair_t pair;

	if (!find_pair_id(id, &idx))
		return;

	pair = obs->hotkeys.hotkey_pairs.array[idx];

	obs_hotkey_set_name(pair.id[0], name0);
	obs_hotkey_set_name(pair.id[1], name1);
}