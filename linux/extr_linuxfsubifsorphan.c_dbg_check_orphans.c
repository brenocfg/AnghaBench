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
struct ubifs_info {int dummy; } ;
struct check_info {int missing; int /*<<< orphan*/  node; int /*<<< orphan*/  root; scalar_t__ leaf_cnt; scalar_t__ tot_inos; scalar_t__ last_ino; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  UBIFS_MAX_INO_NODE_SZ ; 
 int /*<<< orphan*/  dbg_cmt (char*,scalar_t__) ; 
 int /*<<< orphan*/  dbg_free_check_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_is_chk_orph (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_orphan_check ; 
 int dbg_scan_orphans (struct ubifs_info*,struct check_info*) ; 
 int dbg_walk_index (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct check_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,...) ; 

__attribute__((used)) static int dbg_check_orphans(struct ubifs_info *c)
{
	struct check_info ci;
	int err;

	if (!dbg_is_chk_orph(c))
		return 0;

	ci.last_ino = 0;
	ci.tot_inos = 0;
	ci.missing  = 0;
	ci.leaf_cnt = 0;
	ci.root = RB_ROOT;
	ci.node = kmalloc(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	if (!ci.node) {
		ubifs_err(c, "out of memory");
		return -ENOMEM;
	}

	err = dbg_scan_orphans(c, &ci);
	if (err)
		goto out;

	err = dbg_walk_index(c, &dbg_orphan_check, NULL, &ci);
	if (err) {
		ubifs_err(c, "cannot scan TNC, error %d", err);
		goto out;
	}

	if (ci.missing) {
		ubifs_err(c, "%lu missing orphan(s)", ci.missing);
		err = -EINVAL;
		goto out;
	}

	dbg_cmt("last inode number is %lu", ci.last_ino);
	dbg_cmt("total number of inodes is %lu", ci.tot_inos);
	dbg_cmt("total number of leaf nodes is %llu", ci.leaf_cnt);

out:
	dbg_free_check_tree(&ci.root);
	kfree(ci.node);
	return err;
}