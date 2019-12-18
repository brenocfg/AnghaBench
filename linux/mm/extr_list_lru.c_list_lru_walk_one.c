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
struct mem_cgroup {int dummy; } ;
struct list_lru_node {int /*<<< orphan*/  lock; } ;
struct list_lru {struct list_lru_node* node; } ;
typedef  int /*<<< orphan*/  list_lru_walk_cb ;

/* Variables and functions */
 unsigned long __list_lru_walk_one (struct list_lru_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned long*) ; 
 int /*<<< orphan*/  memcg_cache_id (struct mem_cgroup*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned long
list_lru_walk_one(struct list_lru *lru, int nid, struct mem_cgroup *memcg,
		  list_lru_walk_cb isolate, void *cb_arg,
		  unsigned long *nr_to_walk)
{
	struct list_lru_node *nlru = &lru->node[nid];
	unsigned long ret;

	spin_lock(&nlru->lock);
	ret = __list_lru_walk_one(nlru, memcg_cache_id(memcg), isolate, cb_arg,
				  nr_to_walk);
	spin_unlock(&nlru->lock);
	return ret;
}