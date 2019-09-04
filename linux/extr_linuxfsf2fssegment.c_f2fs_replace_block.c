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
struct f2fs_summary {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  f2fs_do_replace_block (struct f2fs_sb_info*,struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  f2fs_update_data_blkaddr (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_summary (struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

void f2fs_replace_block(struct f2fs_sb_info *sbi, struct dnode_of_data *dn,
				block_t old_addr, block_t new_addr,
				unsigned char version, bool recover_curseg,
				bool recover_newaddr)
{
	struct f2fs_summary sum;

	set_summary(&sum, dn->nid, dn->ofs_in_node, version);

	f2fs_do_replace_block(sbi, &sum, old_addr, new_addr,
					recover_curseg, recover_newaddr);

	f2fs_update_data_blkaddr(dn, new_addr);
}