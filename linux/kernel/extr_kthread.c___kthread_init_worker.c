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
struct lock_class_key {int dummy; } ;
struct kthread_worker {int /*<<< orphan*/  delayed_work_list; int /*<<< orphan*/  work_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class_and_name (int /*<<< orphan*/ *,struct lock_class_key*,char const*) ; 
 int /*<<< orphan*/  memset (struct kthread_worker*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void __kthread_init_worker(struct kthread_worker *worker,
				const char *name,
				struct lock_class_key *key)
{
	memset(worker, 0, sizeof(struct kthread_worker));
	raw_spin_lock_init(&worker->lock);
	lockdep_set_class_and_name(&worker->lock, key, name);
	INIT_LIST_HEAD(&worker->work_list);
	INIT_LIST_HEAD(&worker->delayed_work_list);
}