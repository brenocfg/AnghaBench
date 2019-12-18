#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ registerer_type; int /*<<< orphan*/  registerer; int /*<<< orphan*/  description; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ obs_hotkey_t ;
typedef  scalar_t__ obs_hotkey_id ;
struct TYPE_10__ {size_t num; TYPE_2__* array; } ;
struct TYPE_7__ {scalar_t__ next_id; TYPE_6__ hotkeys; } ;
struct TYPE_9__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 scalar_t__ OBS_HOTKEY_REGISTERER_SOURCE ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_erase (TYPE_6__,size_t) ; 
 int /*<<< orphan*/  find_id (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  hotkey_signal (char*,TYPE_2__*) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  obs_weak_source_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_registerer (TYPE_2__*) ; 
 int /*<<< orphan*/  remove_bindings (scalar_t__) ; 

__attribute__((used)) static inline bool unregister_hotkey(obs_hotkey_id id)
{
	if (id >= obs->hotkeys.next_id)
		return false;

	size_t idx;
	if (!find_id(id, &idx))
		return false;

	obs_hotkey_t *hotkey = &obs->hotkeys.hotkeys.array[idx];

	hotkey_signal("hotkey_unregister", hotkey);

	release_registerer(hotkey);

	bfree(hotkey->name);
	bfree(hotkey->description);

	if (hotkey->registerer_type == OBS_HOTKEY_REGISTERER_SOURCE)
		obs_weak_source_release(hotkey->registerer);

	da_erase(obs->hotkeys.hotkeys, idx);
	remove_bindings(id);

	return obs->hotkeys.hotkeys.num >= idx;
}