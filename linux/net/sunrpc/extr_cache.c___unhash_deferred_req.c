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
struct cache_deferred_req {int /*<<< orphan*/  recent; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_defer_cnt ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __unhash_deferred_req(struct cache_deferred_req *dreq)
{
	hlist_del_init(&dreq->hash);
	if (!list_empty(&dreq->recent)) {
		list_del_init(&dreq->recent);
		cache_defer_cnt--;
	}
}