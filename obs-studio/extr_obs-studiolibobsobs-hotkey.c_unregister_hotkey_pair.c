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
struct TYPE_6__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_2__ obs_hotkey_pair_t ;
typedef  scalar_t__ obs_hotkey_pair_id ;
struct TYPE_8__ {size_t num; TYPE_2__* array; } ;
struct TYPE_5__ {scalar_t__ next_pair_id; TYPE_4__ hotkey_pairs; } ;
struct TYPE_7__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase (TYPE_4__,size_t) ; 
 int /*<<< orphan*/  find_pair_id (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  fixup_pointers () ; 
 TYPE_3__* obs ; 
 int unregister_hotkey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool unregister_hotkey_pair(obs_hotkey_pair_id id)
{
	if (id >= obs->hotkeys.next_pair_id)
		return false;

	size_t idx;
	if (!find_pair_id(id, &idx))
		return false;

	obs_hotkey_pair_t *pair = &obs->hotkeys.hotkey_pairs.array[idx];

	bool need_fixup = unregister_hotkey(pair->id[0]);
	need_fixup = unregister_hotkey(pair->id[1]) || need_fixup;
	if (need_fixup)
		fixup_pointers();

	da_erase(obs->hotkeys.hotkey_pairs, idx);
	return obs->hotkeys.hotkey_pairs.num >= idx;
}