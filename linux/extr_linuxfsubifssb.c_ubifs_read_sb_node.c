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
struct ubifs_sb_node {int dummy; } ;
struct ubifs_info {int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct ubifs_sb_node* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  UBIFS_SB_LNUM ; 
 int /*<<< orphan*/  UBIFS_SB_NODE ; 
 int /*<<< orphan*/  UBIFS_SB_NODE_SZ ; 
 int /*<<< orphan*/  kfree (struct ubifs_sb_node*) ; 
 struct ubifs_sb_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_read_node (struct ubifs_info*,struct ubifs_sb_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ubifs_sb_node *ubifs_read_sb_node(struct ubifs_info *c)
{
	struct ubifs_sb_node *sup;
	int err;

	sup = kmalloc(ALIGN(UBIFS_SB_NODE_SZ, c->min_io_size), GFP_NOFS);
	if (!sup)
		return ERR_PTR(-ENOMEM);

	err = ubifs_read_node(c, sup, UBIFS_SB_NODE, UBIFS_SB_NODE_SZ,
			      UBIFS_SB_LNUM, 0);
	if (err) {
		kfree(sup);
		return ERR_PTR(err);
	}

	return sup;
}