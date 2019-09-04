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
struct inode {int dummy; } ;
struct dnode_of_data {scalar_t__ ofs_in_node; int /*<<< orphan*/  node_page; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ ADDRS_PER_PAGE (int /*<<< orphan*/ ,struct inode*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_get_next_page_offset (struct dnode_of_data*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_truncate_data_blocks_range (struct dnode_of_data*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int f2fs_truncate_hole(struct inode *inode, pgoff_t pg_start, pgoff_t pg_end)
{
	int err;

	while (pg_start < pg_end) {
		struct dnode_of_data dn;
		pgoff_t end_offset, count;

		set_new_dnode(&dn, inode, NULL, NULL, 0);
		err = f2fs_get_dnode_of_data(&dn, pg_start, LOOKUP_NODE);
		if (err) {
			if (err == -ENOENT) {
				pg_start = f2fs_get_next_page_offset(&dn,
								pg_start);
				continue;
			}
			return err;
		}

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
		count = min(end_offset - dn.ofs_in_node, pg_end - pg_start);

		f2fs_bug_on(F2FS_I_SB(inode), count == 0 || count > end_offset);

		f2fs_truncate_data_blocks_range(&dn, count);
		f2fs_put_dnode(&dn);

		pg_start += count;
	}
	return 0;
}