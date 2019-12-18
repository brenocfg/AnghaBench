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
struct file_lock {int /*<<< orphan*/ * fl_blocker; int /*<<< orphan*/  fl_blocked_member; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_delete_global_blocked (struct file_lock*) ; 

__attribute__((used)) static void __locks_delete_block(struct file_lock *waiter)
{
	locks_delete_global_blocked(waiter);
	list_del_init(&waiter->fl_blocked_member);
	waiter->fl_blocker = NULL;
}