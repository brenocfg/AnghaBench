#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_nlink; scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {int i_ext_last; int /*<<< orphan*/ * i_ext_bh; int /*<<< orphan*/ * i_ac; int /*<<< orphan*/ * i_lc; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  affs_brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  affs_free_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_free_prealloc (struct inode*) ; 
 int /*<<< orphan*/  affs_truncate (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void
affs_evict_inode(struct inode *inode)
{
	unsigned long cache_page;
	pr_debug("evict_inode(ino=%lu, nlink=%u)\n",
		 inode->i_ino, inode->i_nlink);
	truncate_inode_pages_final(&inode->i_data);

	if (!inode->i_nlink) {
		inode->i_size = 0;
		affs_truncate(inode);
	}

	invalidate_inode_buffers(inode);
	clear_inode(inode);
	affs_free_prealloc(inode);
	cache_page = (unsigned long)AFFS_I(inode)->i_lc;
	if (cache_page) {
		pr_debug("freeing ext cache\n");
		AFFS_I(inode)->i_lc = NULL;
		AFFS_I(inode)->i_ac = NULL;
		free_page(cache_page);
	}
	affs_brelse(AFFS_I(inode)->i_ext_bh);
	AFFS_I(inode)->i_ext_last = ~1;
	AFFS_I(inode)->i_ext_bh = NULL;

	if (!inode->i_nlink)
		affs_free_block(inode->i_sb, inode->i_ino);
}