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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_mntpt_expiry_timer ; 
 int /*<<< orphan*/  afs_vfsmounts ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void afs_mntpt_kill_timer(void)
{
	_enter("");

	ASSERT(list_empty(&afs_vfsmounts));
	cancel_delayed_work_sync(&afs_mntpt_expiry_timer);
}