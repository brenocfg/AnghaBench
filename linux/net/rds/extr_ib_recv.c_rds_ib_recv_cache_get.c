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
struct rds_ib_refill_cache {struct list_head* ready; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static struct list_head *rds_ib_recv_cache_get(struct rds_ib_refill_cache *cache)
{
	struct list_head *head = cache->ready;

	if (head) {
		if (!list_empty(head)) {
			cache->ready = head->next;
			list_del_init(head);
		} else
			cache->ready = NULL;
	}

	return head;
}