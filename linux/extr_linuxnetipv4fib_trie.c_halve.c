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
struct trie {int dummy; } ;
struct key_vector {int bits; scalar_t__ pos; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_INIT_PARENT (struct key_vector*,struct key_vector*) ; 
 unsigned long child_length (struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_child (struct key_vector*,unsigned long,struct key_vector*) ; 
 struct key_vector* replace (struct trie*,struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free (struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free_append (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free_init (struct key_vector*) ; 
 struct key_vector* tnode_new (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static struct key_vector *halve(struct trie *t,
				struct key_vector *oldtnode)
{
	struct key_vector *tn;
	unsigned long i;

	pr_debug("In halve\n");

	tn = tnode_new(oldtnode->key, oldtnode->pos + 1, oldtnode->bits - 1);
	if (!tn)
		goto notnode;

	/* prepare oldtnode to be freed */
	tnode_free_init(oldtnode);

	/* Assemble all of the pointers in our cluster, in this case that
	 * represents all of the pointers out of our allocated nodes that
	 * point to existing tnodes and the links between our allocated
	 * nodes.
	 */
	for (i = child_length(oldtnode); i;) {
		struct key_vector *node1 = get_child(oldtnode, --i);
		struct key_vector *node0 = get_child(oldtnode, --i);
		struct key_vector *inode;

		/* At least one of the children is empty */
		if (!node1 || !node0) {
			put_child(tn, i / 2, node1 ? : node0);
			continue;
		}

		/* Two nonempty children */
		inode = tnode_new(node0->key, oldtnode->pos, 1);
		if (!inode)
			goto nomem;
		tnode_free_append(tn, inode);

		/* initialize pointers out of node */
		put_child(inode, 1, node1);
		put_child(inode, 0, node0);
		NODE_INIT_PARENT(inode, tn);

		/* link parent to node */
		put_child(tn, i / 2, inode);
	}

	/* setup the parent pointers into and out of this node */
	return replace(t, oldtnode, tn);
nomem:
	/* all pointers should be clean so we are done */
	tnode_free(tn);
notnode:
	return NULL;
}