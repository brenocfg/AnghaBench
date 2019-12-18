#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_hotkey_callback_router_func ;
struct TYPE_3__ {void* router_func_data; int /*<<< orphan*/  router_func; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock () ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_set_callback_routing_func(obs_hotkey_callback_router_func func,
					  void *data)
{
	if (!lock())
		return;

	obs->hotkeys.router_func = func;
	obs->hotkeys.router_func_data = data;
	unlock();
}