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
struct list_lru_one {int /*<<< orphan*/  nr_items; int /*<<< orphan*/  list; } ;
struct list_lru_node {int /*<<< orphan*/  lock; int /*<<< orphan*/  nr_items; } ;
struct list_lru {struct list_lru_node* node; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 struct list_lru_one* list_lru_from_kmem (struct list_lru_node*,struct list_head*,struct mem_cgroup**) ; 
 int /*<<< orphan*/  lru_shrinker_id (struct list_lru*) ; 
 int /*<<< orphan*/  memcg_set_shrinker_bit (struct mem_cgroup*,int,int /*<<< orphan*/ ) ; 
 int page_to_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (struct list_head*) ; 

bool list_lru_add(struct list_lru *lru, struct list_head *item)
{
	int nid = page_to_nid(virt_to_page(item));
	struct list_lru_node *nlru = &lru->node[nid];
	struct mem_cgroup *memcg;
	struct list_lru_one *l;

	spin_lock(&nlru->lock);
	if (list_empty(item)) {
		l = list_lru_from_kmem(nlru, item, &memcg);
		list_add_tail(item, &l->list);
		/* Set shrinker bit if the first element was added */
		if (!l->nr_items++)
			memcg_set_shrinker_bit(memcg, nid,
					       lru_shrinker_id(lru));
		nlru->nr_items++;
		spin_unlock(&nlru->lock);
		return true;
	}
	spin_unlock(&nlru->lock);
	return false;
}