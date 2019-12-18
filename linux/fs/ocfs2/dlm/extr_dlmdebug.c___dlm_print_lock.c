#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  node; int /*<<< orphan*/  convert_type; int /*<<< orphan*/  type; } ;
struct dlm_lock {int /*<<< orphan*/  spinlock; scalar_t__ unlock_pending; scalar_t__ cancel_pending; scalar_t__ lock_pending; scalar_t__ convert_pending; scalar_t__ bast_pending; int /*<<< orphan*/  bast_list; scalar_t__ ast_pending; int /*<<< orphan*/  ast_list; int /*<<< orphan*/  lock_refs; TYPE_1__ ml; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dlm_print_lock(struct dlm_lock *lock)
{
	spin_lock(&lock->spinlock);

	printk("    type=%d, conv=%d, node=%u, cookie=%u:%llu, "
	       "ref=%u, ast=(empty=%c,pend=%c), bast=(empty=%c,pend=%c), "
	       "pending=(conv=%c,lock=%c,cancel=%c,unlock=%c)\n",
	       lock->ml.type, lock->ml.convert_type, lock->ml.node,
	       dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	       dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
	       kref_read(&lock->lock_refs),
	       (list_empty(&lock->ast_list) ? 'y' : 'n'),
	       (lock->ast_pending ? 'y' : 'n'),
	       (list_empty(&lock->bast_list) ? 'y' : 'n'),
	       (lock->bast_pending ? 'y' : 'n'),
	       (lock->convert_pending ? 'y' : 'n'),
	       (lock->lock_pending ? 'y' : 'n'),
	       (lock->cancel_pending ? 'y' : 'n'),
	       (lock->unlock_pending ? 'y' : 'n'));

	spin_unlock(&lock->spinlock);
}