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
struct list_head {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 
 int /*<<< orphan*/  locks_unlink_lock_ctx (struct file_lock*) ; 

__attribute__((used)) static void
locks_delete_lock_ctx(struct file_lock *fl, struct list_head *dispose)
{
	locks_unlink_lock_ctx(fl);
	if (dispose)
		list_add(&fl->fl_list, dispose);
	else
		locks_free_lock(fl);
}