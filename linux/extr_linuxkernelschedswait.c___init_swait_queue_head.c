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
struct swait_queue_head {int /*<<< orphan*/  task_list; int /*<<< orphan*/  lock; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class_and_name (int /*<<< orphan*/ *,struct lock_class_key*,char const*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void __init_swait_queue_head(struct swait_queue_head *q, const char *name,
			     struct lock_class_key *key)
{
	raw_spin_lock_init(&q->lock);
	lockdep_set_class_and_name(&q->lock, key, name);
	INIT_LIST_HEAD(&q->task_list);
}