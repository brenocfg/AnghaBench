#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_key_combination_t ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ obs_hotkey_t ;
struct TYPE_9__ {TYPE_2__* hotkey; int /*<<< orphan*/  hotkey_id; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ obs_hotkey_binding_t ;
struct TYPE_7__ {int /*<<< orphan*/  bindings; } ;
struct TYPE_10__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 TYPE_3__* da_push_back_new (int /*<<< orphan*/ ) ; 
 TYPE_4__* obs ; 

__attribute__((used)) static inline void create_binding(obs_hotkey_t *hotkey,
				  obs_key_combination_t combo)
{
	obs_hotkey_binding_t *binding = da_push_back_new(obs->hotkeys.bindings);
	if (!binding)
		return;

	binding->key = combo;
	binding->hotkey_id = hotkey->id;
	binding->hotkey = hotkey;
}