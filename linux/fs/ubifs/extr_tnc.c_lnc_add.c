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
struct ubifs_zbranch {scalar_t__ len; void* leaf; int /*<<< orphan*/  key; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dump_stack () ; 
 int is_hash_key (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 void* kmemdup (void const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,struct ubifs_dent_node const*) ; 
 int ubifs_validate_entry (struct ubifs_info*,struct ubifs_dent_node const*) ; 

__attribute__((used)) static int lnc_add(struct ubifs_info *c, struct ubifs_zbranch *zbr,
		   const void *node)
{
	int err;
	void *lnc_node;
	const struct ubifs_dent_node *dent = node;

	ubifs_assert(c, !zbr->leaf);
	ubifs_assert(c, zbr->len != 0);
	ubifs_assert(c, is_hash_key(c, &zbr->key));

	err = ubifs_validate_entry(c, dent);
	if (err) {
		dump_stack();
		ubifs_dump_node(c, dent);
		return err;
	}

	lnc_node = kmemdup(node, zbr->len, GFP_NOFS);
	if (!lnc_node)
		/* We don't have to have the cache, so no error */
		return 0;

	zbr->leaf = lnc_node;
	return 0;
}