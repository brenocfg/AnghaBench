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
struct ubifs_pnode {int dummy; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_pnode*) ; 
 int PTR_ERR (struct ubifs_pnode*) ; 
 int /*<<< orphan*/  do_make_pnode_dirty (struct ubifs_info*,struct ubifs_pnode*) ; 
 struct ubifs_pnode* next_pnode_to_dirty (struct ubifs_info*,struct ubifs_pnode*) ; 
 struct ubifs_pnode* ubifs_pnode_lookup (struct ubifs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_tree_dirty(struct ubifs_info *c)
{
	struct ubifs_pnode *pnode;

	pnode = ubifs_pnode_lookup(c, 0);
	if (IS_ERR(pnode))
		return PTR_ERR(pnode);

	while (pnode) {
		do_make_pnode_dirty(c, pnode);
		pnode = next_pnode_to_dirty(c, pnode);
		if (IS_ERR(pnode))
			return PTR_ERR(pnode);
	}
	return 0;
}