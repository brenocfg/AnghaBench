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
struct futex_q {union futex_key key; int /*<<< orphan*/ * lock_ptr; int /*<<< orphan*/  list; } ;
struct futex_hash_bucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_futex_key_refs (union futex_key*) ; 
 int /*<<< orphan*/  hb_waiters_dec (struct futex_hash_bucket*) ; 
 int /*<<< orphan*/  hb_waiters_inc (struct futex_hash_bucket*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  plist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void requeue_futex(struct futex_q *q, struct futex_hash_bucket *hb1,
		   struct futex_hash_bucket *hb2, union futex_key *key2)
{

	/*
	 * If key1 and key2 hash to the same bucket, no need to
	 * requeue.
	 */
	if (likely(&hb1->chain != &hb2->chain)) {
		plist_del(&q->list, &hb1->chain);
		hb_waiters_dec(hb1);
		hb_waiters_inc(hb2);
		plist_add(&q->list, &hb2->chain);
		q->lock_ptr = &hb2->lock;
	}
	get_futex_key_refs(key2);
	q->key = *key2;
}