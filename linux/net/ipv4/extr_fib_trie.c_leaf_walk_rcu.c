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
typedef  scalar_t__ t_key ;
struct key_vector {scalar_t__ key; unsigned long bits; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct key_vector*) ; 
 scalar_t__ IS_TNODE (struct key_vector*) ; 
 int /*<<< orphan*/  IS_TRIE (struct key_vector*) ; 
 struct key_vector* get_child_rcu (struct key_vector*,int /*<<< orphan*/ ) ; 
 int get_index (scalar_t__,struct key_vector*) ; 
 struct key_vector* node_parent_rcu (struct key_vector*) ; 

__attribute__((used)) static struct key_vector *leaf_walk_rcu(struct key_vector **tn, t_key key)
{
	struct key_vector *pn, *n = *tn;
	unsigned long cindex;

	/* this loop is meant to try and find the key in the trie */
	do {
		/* record parent and next child index */
		pn = n;
		cindex = (key > pn->key) ? get_index(key, pn) : 0;

		if (cindex >> pn->bits)
			break;

		/* descend into the next child */
		n = get_child_rcu(pn, cindex++);
		if (!n)
			break;

		/* guarantee forward progress on the keys */
		if (IS_LEAF(n) && (n->key >= key))
			goto found;
	} while (IS_TNODE(n));

	/* this loop will search for the next leaf with a greater key */
	while (!IS_TRIE(pn)) {
		/* if we exhausted the parent node we will need to climb */
		if (cindex >= (1ul << pn->bits)) {
			t_key pkey = pn->key;

			pn = node_parent_rcu(pn);
			cindex = get_index(pkey, pn) + 1;
			continue;
		}

		/* grab the next available node */
		n = get_child_rcu(pn, cindex++);
		if (!n)
			continue;

		/* no need to compare keys since we bumped the index */
		if (IS_LEAF(n))
			goto found;

		/* Rescan start scanning in new node */
		pn = n;
		cindex = 0;
	}

	*tn = pn;
	return NULL; /* Root of trie */
found:
	/* if we are at the limit for keys just return NULL for the tnode */
	*tn = pn;
	return n;
}