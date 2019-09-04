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
struct pneigh_entry {struct net_device* dev; struct pneigh_entry* next; int /*<<< orphan*/  key; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct neigh_table {unsigned int key_len; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* pdestructor ) (struct pneigh_entry*) ;struct pneigh_entry** phash_buckets; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct pneigh_entry*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 size_t pneigh_hash (void const*,unsigned int) ; 
 int /*<<< orphan*/  pneigh_net (struct pneigh_entry*) ; 
 int /*<<< orphan*/  stub1 (struct pneigh_entry*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int pneigh_delete(struct neigh_table *tbl, struct net *net, const void *pkey,
		  struct net_device *dev)
{
	struct pneigh_entry *n, **np;
	unsigned int key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	write_lock_bh(&tbl->lock);
	for (np = &tbl->phash_buckets[hash_val]; (n = *np) != NULL;
	     np = &n->next) {
		if (!memcmp(n->key, pkey, key_len) && n->dev == dev &&
		    net_eq(pneigh_net(n), net)) {
			*np = n->next;
			write_unlock_bh(&tbl->lock);
			if (tbl->pdestructor)
				tbl->pdestructor(n);
			if (n->dev)
				dev_put(n->dev);
			kfree(n);
			return 0;
		}
	}
	write_unlock_bh(&tbl->lock);
	return -ENOENT;
}