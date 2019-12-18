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
struct rhashtable {int dummy; } ;
struct rhash_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 void* rhashtable_try_insert (struct rhashtable*,void const*,struct rhash_head*) ; 

void *rhashtable_insert_slow(struct rhashtable *ht, const void *key,
			     struct rhash_head *obj)
{
	void *data;

	do {
		rcu_read_lock();
		data = rhashtable_try_insert(ht, key, obj);
		rcu_read_unlock();
	} while (PTR_ERR(data) == -EAGAIN);

	return data;
}