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
typedef  int /*<<< orphan*/  u32 ;
struct trie {struct key_vector* kv; } ;
struct key_vector {unsigned long bits; } ;

/* Variables and functions */
 scalar_t__ IS_TNODE (struct key_vector*) ; 
 struct key_vector* get_child_rcu (struct key_vector*,unsigned long) ; 
 unsigned long get_cindex (int /*<<< orphan*/ ,struct key_vector*) ; 

__attribute__((used)) static struct key_vector *fib_find_node(struct trie *t,
					struct key_vector **tp, u32 key)
{
	struct key_vector *pn, *n = t->kv;
	unsigned long index = 0;

	do {
		pn = n;
		n = get_child_rcu(n, index);

		if (!n)
			break;

		index = get_cindex(key, n);

		/* This bit of code is a bit tricky but it combines multiple
		 * checks into a single check.  The prefix consists of the
		 * prefix plus zeros for the bits in the cindex. The index
		 * is the difference between the key and this value.  From
		 * this we can actually derive several pieces of data.
		 *   if (index >= (1ul << bits))
		 *     we have a mismatch in skip bits and failed
		 *   else
		 *     we know the value is cindex
		 *
		 * This check is safe even if bits == KEYLENGTH due to the
		 * fact that we can only allocate a node with 32 bits if a
		 * long is greater than 32 bits.
		 */
		if (index >= (1ul << n->bits)) {
			n = NULL;
			break;
		}

		/* keep searching until we find a perfect match leaf or NULL */
	} while (IS_TNODE(n));

	*tp = pn;

	return n;
}