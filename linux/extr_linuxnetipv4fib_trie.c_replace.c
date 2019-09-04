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
struct key_vector {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_INIT_PARENT (struct key_vector*,struct key_vector*) ; 
 unsigned long child_length (struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 struct key_vector* node_parent (struct key_vector*) ; 
 int /*<<< orphan*/  put_child_root (struct key_vector*,int /*<<< orphan*/ ,struct key_vector*) ; 
 struct key_vector* resize (struct trie*,struct key_vector*) ; 
 int /*<<< orphan*/  tnode_free (struct key_vector*) ; 
 scalar_t__ tnode_full (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  update_children (struct key_vector*) ; 

__attribute__((used)) static struct key_vector *replace(struct trie *t,
				  struct key_vector *oldtnode,
				  struct key_vector *tn)
{
	struct key_vector *tp = node_parent(oldtnode);
	unsigned long i;

	/* setup the parent pointer out of and back into this node */
	NODE_INIT_PARENT(tn, tp);
	put_child_root(tp, tn->key, tn);

	/* update all of the child parent pointers */
	update_children(tn);

	/* all pointers should be clean so we are done */
	tnode_free(oldtnode);

	/* resize children now that oldtnode is freed */
	for (i = child_length(tn); i;) {
		struct key_vector *inode = get_child(tn, --i);

		/* resize child node */
		if (tnode_full(tn, inode))
			tn = resize(t, inode);
	}

	return tp;
}