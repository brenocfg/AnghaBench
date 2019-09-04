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
struct dlm_ls {int /*<<< orphan*/  ls_debug_toss_dentry; int /*<<< orphan*/  ls_debug_all_dentry; int /*<<< orphan*/  ls_debug_locks_dentry; int /*<<< orphan*/  ls_debug_waiters_dentry; int /*<<< orphan*/  ls_debug_rsb_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void dlm_delete_debug_file(struct dlm_ls *ls)
{
	debugfs_remove(ls->ls_debug_rsb_dentry);
	debugfs_remove(ls->ls_debug_waiters_dentry);
	debugfs_remove(ls->ls_debug_locks_dentry);
	debugfs_remove(ls->ls_debug_all_dentry);
	debugfs_remove(ls->ls_debug_toss_dentry);
}