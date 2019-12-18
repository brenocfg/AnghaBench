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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ;scalar_t__ pressed; } ;
typedef  TYPE_2__ obs_hotkey_t ;
struct TYPE_9__ {int pressed; TYPE_2__* hotkey; } ;
typedef  TYPE_3__ obs_hotkey_binding_t ;
struct TYPE_7__ {int /*<<< orphan*/  router_func_data; int /*<<< orphan*/  (* router_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  reroute_hotkeys; } ;
struct TYPE_10__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 TYPE_6__* obs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void release_pressed_binding(obs_hotkey_binding_t *binding)
{
	binding->pressed = false;

	obs_hotkey_t *hotkey = binding->hotkey;
	if (--hotkey->pressed)
		return;

	if (!obs->hotkeys.reroute_hotkeys)
		hotkey->func(hotkey->data, hotkey->id, hotkey, false);
	else if (obs->hotkeys.router_func)
		obs->hotkeys.router_func(obs->hotkeys.router_func_data,
					 hotkey->id, false);
}