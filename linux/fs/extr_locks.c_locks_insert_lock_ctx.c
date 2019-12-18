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
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  locks_insert_global_locks (struct file_lock*) ; 

__attribute__((used)) static void
locks_insert_lock_ctx(struct file_lock *fl, struct list_head *before)
{
	list_add_tail(&fl->fl_list, before);
	locks_insert_global_locks(fl);
}