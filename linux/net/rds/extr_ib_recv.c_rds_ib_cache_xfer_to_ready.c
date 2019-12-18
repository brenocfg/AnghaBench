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
struct rds_ib_refill_cache {struct list_head* ready; int /*<<< orphan*/  xfer; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_entire_tail (struct list_head*,struct list_head*) ; 
 struct list_head* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_cache_xfer_to_ready(struct rds_ib_refill_cache *cache)
{
	struct list_head *tmp;

	tmp = xchg(&cache->xfer, NULL);
	if (tmp) {
		if (cache->ready)
			list_splice_entire_tail(tmp, cache->ready);
		else
			cache->ready = tmp;
	}
}