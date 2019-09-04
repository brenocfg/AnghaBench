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
typedef  int t_key ;
struct trie {int dummy; } ;
struct key_vector {int key; } ;
struct fib_alias {int /*<<< orphan*/  fa_slen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NODE_INIT_PARENT (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  __fls (int) ; 
 struct key_vector* get_child (struct key_vector*,int) ; 
 int get_index (int,struct key_vector*) ; 
 struct key_vector* leaf_new (int,struct fib_alias*) ; 
 int /*<<< orphan*/  node_free (struct key_vector*) ; 
 int /*<<< orphan*/  node_push_suffix (struct key_vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_set_parent (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  put_child (struct key_vector*,int,struct key_vector*) ; 
 int /*<<< orphan*/  put_child_root (struct key_vector*,int,struct key_vector*) ; 
 struct key_vector* tnode_new (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trie_rebalance (struct trie*,struct key_vector*) ; 

__attribute__((used)) static int fib_insert_node(struct trie *t, struct key_vector *tp,
			   struct fib_alias *new, t_key key)
{
	struct key_vector *n, *l;

	l = leaf_new(key, new);
	if (!l)
		goto noleaf;

	/* retrieve child from parent node */
	n = get_child(tp, get_index(key, tp));

	/* Case 2: n is a LEAF or a TNODE and the key doesn't match.
	 *
	 *  Add a new tnode here
	 *  first tnode need some special handling
	 *  leaves us in position for handling as case 3
	 */
	if (n) {
		struct key_vector *tn;

		tn = tnode_new(key, __fls(key ^ n->key), 1);
		if (!tn)
			goto notnode;

		/* initialize routes out of node */
		NODE_INIT_PARENT(tn, tp);
		put_child(tn, get_index(key, tn) ^ 1, n);

		/* start adding routes into the node */
		put_child_root(tp, key, tn);
		node_set_parent(n, tn);

		/* parent now has a NULL spot where the leaf can go */
		tp = tn;
	}

	/* Case 3: n is NULL, and will just insert a new leaf */
	node_push_suffix(tp, new->fa_slen);
	NODE_INIT_PARENT(l, tp);
	put_child_root(tp, key, l);
	trie_rebalance(t, tp);

	return 0;
notnode:
	node_free(l);
noleaf:
	return -ENOMEM;
}