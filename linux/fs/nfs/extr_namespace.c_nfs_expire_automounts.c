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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mark_mounts_for_expiry (struct list_head*) ; 
 struct list_head nfs_automount_list ; 
 int /*<<< orphan*/  nfs_automount_task ; 
 int /*<<< orphan*/  nfs_mountpoint_expiry_timeout ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_expire_automounts(struct work_struct *work)
{
	struct list_head *list = &nfs_automount_list;

	mark_mounts_for_expiry(list);
	if (!list_empty(list))
		schedule_delayed_work(&nfs_automount_task, nfs_mountpoint_expiry_timeout);
}