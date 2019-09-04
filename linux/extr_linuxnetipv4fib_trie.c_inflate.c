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
struct key_vector {int key; unsigned int pos; int bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_INIT_PARENT (struct key_vector*,struct key_vector*) ; 
 unsigned long child_length (struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 int get_index (int,struct key_vector*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_child (struct key_vector*,int,struct key_vector*) ; 
 struct key_vector* replace (struct trie*,struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free (struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free_append (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free_init (struct key_vector*) ; 
 int /*<<< orphan*/  tnode_full (struct key_vector*,struct key_vector*) ; 
 struct key_vector* tnode_new (int,unsigned int,int) ; 

__attribute__((used)) static struct key_vector *inflate(struct trie *t,
				  struct key_vector *oldtnode)
{
	struct key_vector *tn;
	unsigned long i;
	t_key m;

	pr_debug("In inflate\n");

	tn = tnode_new(oldtnode->key, oldtnode->pos - 1, oldtnode->bits + 1);
	if (!tn)
		goto notnode;

	/* prepare oldtnode to be freed */
	tnode_free_init(oldtnode);

	/* Assemble all of the pointers in our cluster, in this case that
	 * represents all of the pointers out of our allocated nodes that
	 * point to existing tnodes and the links between our allocated
	 * nodes.
	 */
	for (i = child_length(oldtnode), m = 1u << tn->pos; i;) {
		struct key_vector *inode = get_child(oldtnode, --i);
		struct key_vector *node0, *node1;
		unsigned long j, k;

		/* An empty child */
		if (!inode)
			continue;

		/* A leaf or an internal node with skipped bits */
		if (!tnode_full(oldtnode, inode)) {
			put_child(tn, get_index(inode->key, tn), inode);
			continue;
		}

		/* drop the node in the old tnode free list */
		tnode_free_append(oldtnode, inode);

		/* An internal node with two children */
		if (inode->bits == 1) {
			put_child(tn, 2 * i + 1, get_child(inode, 1));
			put_child(tn, 2 * i, get_child(inode, 0));
			continue;
		}

		/* We will replace this node 'inode' with two new
		 * ones, 'node0' and 'node1', each with half of the
		 * original children. The two new nodes will have
		 * a position one bit further down the key and this
		 * means that the "significant" part of their keys
		 * (see the discussion near the top of this file)
		 * will differ by one bit, which will be "0" in
		 * node0's key and "1" in node1's key. Since we are
		 * moving the key position by one step, the bit that
		 * we are moving away from - the bit at position
		 * (tn->pos) - is the one that will differ between
		 * node0 and node1. So... we synthesize that bit in the
		 * two new keys.
		 */
		node1 = tnode_new(inode->key | m, inode->pos, inode->bits - 1);
		if (!node1)
			goto nomem;
		node0 = tnode_new(inode->key, inode->pos, inode->bits - 1);

		tnode_free_append(tn, node1);
		if (!node0)
			goto nomem;
		tnode_free_append(tn, node0);

		/* populate child pointers in new nodes */
		for (k = child_length(inode), j = k / 2; j;) {
			put_child(node1, --j, get_child(inode, --k));
			put_child(node0, j, get_child(inode, j));
			put_child(node1, --j, get_child(inode, --k));
			put_child(node0, j, get_child(inode, j));
		}

		/* link new nodes to parent */
		NODE_INIT_PARENT(node1, tn);
		NODE_INIT_PARENT(node0, tn);

		/* link parent to nodes */
		put_child(tn, 2 * i + 1, node1);
		put_child(tn, 2 * i, node0);
	}

	/* setup the parent pointers into and out of this node */
	return replace(t, oldtnode, tn);
nomem:
	/* all pointers should be clean so we are done */
	tnode_free(tn);
notnode:
	return NULL;
}