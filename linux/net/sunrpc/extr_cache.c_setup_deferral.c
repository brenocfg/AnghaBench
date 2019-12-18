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
struct cache_head {int dummy; } ;
struct cache_deferred_req {int /*<<< orphan*/  recent; struct cache_head* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hash_deferred_req (struct cache_deferred_req*,struct cache_head*) ; 
 int /*<<< orphan*/  cache_defer_cnt ; 
 int /*<<< orphan*/  cache_defer_list ; 
 int /*<<< orphan*/  cache_defer_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_deferral(struct cache_deferred_req *dreq,
			   struct cache_head *item,
			   int count_me)
{

	dreq->item = item;

	spin_lock(&cache_defer_lock);

	__hash_deferred_req(dreq, item);

	if (count_me) {
		cache_defer_cnt++;
		list_add(&dreq->recent, &cache_defer_list);
	}

	spin_unlock(&cache_defer_lock);

}