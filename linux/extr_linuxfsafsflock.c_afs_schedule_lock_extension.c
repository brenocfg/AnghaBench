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
struct afs_vnode {int /*<<< orphan*/  lock_work; } ;

/* Variables and functions */
 int AFS_LOCKWAIT ; 
 int HZ ; 
 int /*<<< orphan*/  afs_lock_manager ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void afs_schedule_lock_extension(struct afs_vnode *vnode)
{
	queue_delayed_work(afs_lock_manager, &vnode->lock_work,
			   AFS_LOCKWAIT * HZ / 2);
}