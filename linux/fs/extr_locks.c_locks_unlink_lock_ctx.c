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
struct file_lock {int /*<<< orphan*/  fl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_delete_global_locks (struct file_lock*) ; 
 int /*<<< orphan*/  locks_wake_up_blocks (struct file_lock*) ; 

__attribute__((used)) static void
locks_unlink_lock_ctx(struct file_lock *fl)
{
	locks_delete_global_locks(fl);
	list_del_init(&fl->fl_list);
	locks_wake_up_blocks(fl);
}