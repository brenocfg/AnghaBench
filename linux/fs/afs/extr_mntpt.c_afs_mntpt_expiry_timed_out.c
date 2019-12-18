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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int afs_mntpt_expiry_timeout ; 
 int /*<<< orphan*/  afs_mntpt_expiry_timer ; 
 int /*<<< orphan*/  afs_vfsmounts ; 
 int /*<<< orphan*/  afs_wq ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_mounts_for_expiry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void afs_mntpt_expiry_timed_out(struct work_struct *work)
{
	_enter("");

	if (!list_empty(&afs_vfsmounts)) {
		mark_mounts_for_expiry(&afs_vfsmounts);
		queue_delayed_work(afs_wq, &afs_mntpt_expiry_timer,
				   afs_mntpt_expiry_timeout * HZ);
	}

	_leave("");
}