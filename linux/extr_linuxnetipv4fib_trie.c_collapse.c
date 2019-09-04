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
 unsigned long child_length (struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 int /*<<< orphan*/  node_free (struct key_vector*) ; 
 struct key_vector* node_parent (struct key_vector*) ; 
 int /*<<< orphan*/  node_set_parent (struct key_vector*,struct key_vector*) ; 
 int /*<<< orphan*/  put_child_root (struct key_vector*,int /*<<< orphan*/ ,struct key_vector*) ; 

__attribute__((used)) static struct key_vector *collapse(struct trie *t,
				   struct key_vector *oldtnode)
{
	struct key_vector *n, *tp;
	unsigned long i;

	/* scan the tnode looking for that one child that might still exist */
	for (n = NULL, i = child_length(oldtnode); !n && i;)
		n = get_child(oldtnode, --i);

	/* compress one level */
	tp = node_parent(oldtnode);
	put_child_root(tp, oldtnode->key, n);
	node_set_parent(n, tp);

	/* drop dead node */
	node_free(oldtnode);

	return tp;
}