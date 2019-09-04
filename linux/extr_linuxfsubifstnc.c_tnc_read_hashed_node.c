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
struct ubifs_zbranch {scalar_t__ len; int /*<<< orphan*/  key; scalar_t__ leaf; } ;
struct ubifs_info {scalar_t__ replaying; } ;

/* Variables and functions */
 int ENOENT ; 
 int fallible_read_node (struct ubifs_info*,int /*<<< orphan*/ *,struct ubifs_zbranch*,void*) ; 
 int is_hash_key (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int lnc_add (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_tnc_read_node (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 

__attribute__((used)) static int tnc_read_hashed_node(struct ubifs_info *c, struct ubifs_zbranch *zbr,
				void *node)
{
	int err;

	ubifs_assert(c, is_hash_key(c, &zbr->key));

	if (zbr->leaf) {
		/* Read from the leaf node cache */
		ubifs_assert(c, zbr->len != 0);
		memcpy(node, zbr->leaf, zbr->len);
		return 0;
	}

	if (c->replaying) {
		err = fallible_read_node(c, &zbr->key, zbr, node);
		/*
		 * When the node was not found, return -ENOENT, 0 otherwise.
		 * Negative return codes stay as-is.
		 */
		if (err == 0)
			err = -ENOENT;
		else if (err == 1)
			err = 0;
	} else {
		err = ubifs_tnc_read_node(c, zbr, node);
	}
	if (err)
		return err;

	/* Add the node to the leaf node cache */
	err = lnc_add(c, zbr, node);
	return err;
}