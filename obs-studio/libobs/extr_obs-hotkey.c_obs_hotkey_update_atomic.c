#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  (* obs_hotkey_atomic_update_func ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_update_atomic(obs_hotkey_atomic_update_func func, void *data)
{
	if (!lock())
		return;

	func(data);

	unlock();
}