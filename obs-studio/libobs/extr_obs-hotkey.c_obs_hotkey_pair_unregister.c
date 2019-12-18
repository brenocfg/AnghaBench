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
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;

/* Variables and functions */
 int /*<<< orphan*/  fixup_pair_pointers () ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  unlock () ; 
 scalar_t__ unregister_hotkey_pair (int /*<<< orphan*/ ) ; 

void obs_hotkey_pair_unregister(obs_hotkey_pair_id id)
{
	if (!lock())
		return;

	if (unregister_hotkey_pair(id))
		fixup_pair_pointers();

	unlock();
}