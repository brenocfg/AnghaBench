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
struct ubifs_zbranch {scalar_t__ len; void* leaf; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int ubifs_validate_entry (struct ubifs_info*,void*) ; 

__attribute__((used)) static int lnc_add_directly(struct ubifs_info *c, struct ubifs_zbranch *zbr,
			    void *node)
{
	int err;

	ubifs_assert(c, !zbr->leaf);
	ubifs_assert(c, zbr->len != 0);

	err = ubifs_validate_entry(c, node);
	if (err) {
		dump_stack();
		ubifs_dump_node(c, node);
		return err;
	}

	zbr->leaf = node;
	return 0;
}