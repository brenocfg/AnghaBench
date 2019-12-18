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
typedef  size_t u32 ;
struct pneigh_entry {struct net_device* dev; struct pneigh_entry* next; } ;
struct net_device {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  (* pdestructor ) (struct pneigh_entry*) ;int /*<<< orphan*/  lock; struct pneigh_entry** phash_buckets; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t PNEIGH_HASHMASK ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct pneigh_entry*) ; 
 int /*<<< orphan*/  stub1 (struct pneigh_entry*) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pneigh_ifdown_and_unlock(struct neigh_table *tbl,
				    struct net_device *dev)
{
	struct pneigh_entry *n, **np, *freelist = NULL;
	u32 h;

	for (h = 0; h <= PNEIGH_HASHMASK; h++) {
		np = &tbl->phash_buckets[h];
		while ((n = *np) != NULL) {
			if (!dev || n->dev == dev) {
				*np = n->next;
				n->next = freelist;
				freelist = n;
				continue;
			}
			np = &n->next;
		}
	}
	write_unlock_bh(&tbl->lock);
	while ((n = freelist)) {
		freelist = n->next;
		n->next = NULL;
		if (tbl->pdestructor)
			tbl->pdestructor(n);
		if (n->dev)
			dev_put(n->dev);
		kfree(n);
	}
	return -ENOENT;
}