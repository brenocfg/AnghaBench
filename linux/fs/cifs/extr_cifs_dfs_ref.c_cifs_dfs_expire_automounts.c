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
 struct list_head cifs_dfs_automount_list ; 
 int /*<<< orphan*/  cifs_dfs_automount_task ; 
 int /*<<< orphan*/  cifs_dfs_mountpoint_expiry_timeout ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mark_mounts_for_expiry (struct list_head*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cifs_dfs_expire_automounts(struct work_struct *work)
{
	struct list_head *list = &cifs_dfs_automount_list;

	mark_mounts_for_expiry(list);
	if (!list_empty(list))
		schedule_delayed_work(&cifs_dfs_automount_task,
				      cifs_dfs_mountpoint_expiry_timeout);
}