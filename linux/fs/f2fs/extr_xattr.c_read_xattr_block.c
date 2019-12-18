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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_xattr_nid; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  VALID_XATTR_BLOCK_SIZE ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int inline_xattr_size (struct inode*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static int read_xattr_block(struct inode *inode, void *txattr_addr)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	unsigned int inline_size = inline_xattr_size(inode);
	struct page *xpage;
	void *xattr_addr;

	/* The inode already has an extended attribute block. */
	xpage = f2fs_get_node_page(sbi, xnid);
	if (IS_ERR(xpage))
		return PTR_ERR(xpage);

	xattr_addr = page_address(xpage);
	memcpy(txattr_addr + inline_size, xattr_addr, VALID_XATTR_BLOCK_SIZE);
	f2fs_put_page(xpage, 1);

	return 0;
}