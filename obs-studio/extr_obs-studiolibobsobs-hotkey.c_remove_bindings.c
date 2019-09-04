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
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_hotkey_id ;
struct TYPE_7__ {scalar_t__ pressed; } ;
typedef  TYPE_2__ obs_hotkey_binding_t ;
struct TYPE_9__ {TYPE_2__* array; } ;
struct TYPE_6__ {TYPE_5__ bindings; } ;
struct TYPE_8__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase (TYPE_5__,size_t) ; 
 scalar_t__ find_binding (int /*<<< orphan*/ ,size_t*) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  release_pressed_binding (TYPE_2__*) ; 

__attribute__((used)) static inline void remove_bindings(obs_hotkey_id id)
{
	size_t idx;
	while (find_binding(id, &idx)) {
		obs_hotkey_binding_t *binding =
			&obs->hotkeys.bindings.array[idx];

		if (binding->pressed)
			release_pressed_binding(binding);

		da_erase(obs->hotkeys.bindings, idx);
	}
}