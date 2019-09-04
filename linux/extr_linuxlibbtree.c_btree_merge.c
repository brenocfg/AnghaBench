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
struct btree_head {int /*<<< orphan*/  height; int /*<<< orphan*/  node; } ;
struct btree_geo {int /*<<< orphan*/  keylen; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_KEYLEN ; 
 int /*<<< orphan*/  __btree_init (struct btree_head*) ; 
 int btree_insert (struct btree_head*,struct btree_geo*,unsigned long*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btree_last (struct btree_head*,struct btree_geo*,unsigned long*) ; 
 void* btree_lookup (struct btree_head*,struct btree_geo*,unsigned long*) ; 
 int /*<<< orphan*/  btree_remove (struct btree_head*,struct btree_geo*,unsigned long*) ; 
 int /*<<< orphan*/  longcpy (unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 

int btree_merge(struct btree_head *target, struct btree_head *victim,
		struct btree_geo *geo, gfp_t gfp)
{
	unsigned long key[MAX_KEYLEN];
	unsigned long dup[MAX_KEYLEN];
	void *val;
	int err;

	BUG_ON(target == victim);

	if (!(target->node)) {
		/* target is empty, just copy fields over */
		target->node = victim->node;
		target->height = victim->height;
		__btree_init(victim);
		return 0;
	}

	/* TODO: This needs some optimizations.  Currently we do three tree
	 * walks to remove a single object from the victim.
	 */
	for (;;) {
		if (!btree_last(victim, geo, key))
			break;
		val = btree_lookup(victim, geo, key);
		err = btree_insert(target, geo, key, val, gfp);
		if (err)
			return err;
		/* We must make a copy of the key, as the original will get
		 * mangled inside btree_remove. */
		longcpy(dup, key, geo->keylen);
		btree_remove(victim, geo, dup);
	}
	return 0;
}