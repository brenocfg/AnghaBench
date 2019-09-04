#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ max; } ;
struct xt_hashlimit_htable {int rnd_initialized; scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * hash; TYPE_1__ cfg; int /*<<< orphan*/  rnd; } ;
struct dsthash_ent {int /*<<< orphan*/  node; int /*<<< orphan*/  lock; int /*<<< orphan*/  dst; } ;
struct dsthash_dst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct dsthash_ent* dsthash_find (struct xt_hashlimit_htable*,struct dsthash_dst const*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 size_t hash_dst (struct xt_hashlimit_htable*,struct dsthash_dst const*) ; 
 int /*<<< orphan*/  hashlimit_cachep ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dsthash_ent* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dsthash_dst const*,int) ; 
 int /*<<< orphan*/  net_err_ratelimited (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dsthash_ent *
dsthash_alloc_init(struct xt_hashlimit_htable *ht,
		   const struct dsthash_dst *dst, bool *race)
{
	struct dsthash_ent *ent;

	spin_lock(&ht->lock);

	/* Two or more packets may race to create the same entry in the
	 * hashtable, double check if this packet lost race.
	 */
	ent = dsthash_find(ht, dst);
	if (ent != NULL) {
		spin_unlock(&ht->lock);
		*race = true;
		return ent;
	}

	/* initialize hash with random val at the time we allocate
	 * the first hashtable entry */
	if (unlikely(!ht->rnd_initialized)) {
		get_random_bytes(&ht->rnd, sizeof(ht->rnd));
		ht->rnd_initialized = true;
	}

	if (ht->cfg.max && ht->count >= ht->cfg.max) {
		/* FIXME: do something. question is what.. */
		net_err_ratelimited("max count of %u reached\n", ht->cfg.max);
		ent = NULL;
	} else
		ent = kmem_cache_alloc(hashlimit_cachep, GFP_ATOMIC);
	if (ent) {
		memcpy(&ent->dst, dst, sizeof(ent->dst));
		spin_lock_init(&ent->lock);

		spin_lock(&ent->lock);
		hlist_add_head_rcu(&ent->node, &ht->hash[hash_dst(ht, dst)]);
		ht->count++;
	}
	spin_unlock(&ht->lock);
	return ent;
}