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
typedef  union futex_key {int dummy; } futex_key ;
struct futex_q {int /*<<< orphan*/  task; int /*<<< orphan*/ * lock_ptr; int /*<<< orphan*/ * rt_waiter; union futex_key key; } ;
struct futex_hash_bucket {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __unqueue_futex (struct futex_q*) ; 
 int /*<<< orphan*/  get_futex_key_refs (union futex_key*) ; 
 int /*<<< orphan*/  wake_up_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void requeue_pi_wake_futex(struct futex_q *q, union futex_key *key,
			   struct futex_hash_bucket *hb)
{
	get_futex_key_refs(key);
	q->key = *key;

	__unqueue_futex(q);

	WARN_ON(!q->rt_waiter);
	q->rt_waiter = NULL;

	q->lock_ptr = &hb->lock;

	wake_up_state(q->task, TASK_NORMAL);
}