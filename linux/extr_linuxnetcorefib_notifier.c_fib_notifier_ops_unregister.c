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
struct fib_notifier_ops {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct fib_notifier_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

void fib_notifier_ops_unregister(struct fib_notifier_ops *ops)
{
	list_del_rcu(&ops->list);
	kfree_rcu(ops, rcu);
}