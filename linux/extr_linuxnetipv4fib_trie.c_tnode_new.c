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
typedef  unsigned int t_key ;
struct tnode {int full_children; unsigned long empty_children; struct key_vector* kv; } ;
struct key_vector {unsigned int key; int pos; int bits; int slen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int KEYLENGTH ; 
 int /*<<< orphan*/  TNODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tnode*,int /*<<< orphan*/ ,int) ; 
 struct tnode* tnode_alloc (int) ; 

__attribute__((used)) static struct key_vector *tnode_new(t_key key, int pos, int bits)
{
	unsigned int shift = pos + bits;
	struct key_vector *tn;
	struct tnode *tnode;

	/* verify bits and pos their msb bits clear and values are valid */
	BUG_ON(!bits || (shift > KEYLENGTH));

	tnode = tnode_alloc(bits);
	if (!tnode)
		return NULL;

	pr_debug("AT %p s=%zu %zu\n", tnode, TNODE_SIZE(0),
		 sizeof(struct key_vector *) << bits);

	if (bits == KEYLENGTH)
		tnode->full_children = 1;
	else
		tnode->empty_children = 1ul << bits;

	tn = tnode->kv;
	tn->key = (shift < KEYLENGTH) ? (key >> shift) << shift : 0;
	tn->pos = pos;
	tn->bits = bits;
	tn->slen = pos;

	return tn;
}