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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode {int i_inline; int /*<<< orphan*/  i_extra_isize; } ;
struct TYPE_2__ {struct f2fs_inode i; } ;

/* Variables and functions */
 int F2FS_EXTRA_ATTR ; 
 int /*<<< orphan*/  F2FS_FITS_IN_INODE (struct f2fs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  IS_INODE (struct page*) ; 
 int /*<<< orphan*/  f2fs_sb_has_inode_chksum (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  i_inode_checksum ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool f2fs_enable_inode_chksum(struct f2fs_sb_info *sbi, struct page *page)
{
	struct f2fs_inode *ri = &F2FS_NODE(page)->i;

	if (!f2fs_sb_has_inode_chksum(sbi))
		return false;

	if (!IS_INODE(page) || !(ri->i_inline & F2FS_EXTRA_ATTR))
		return false;

	if (!F2FS_FITS_IN_INODE(ri, le16_to_cpu(ri->i_extra_isize),
				i_inode_checksum))
		return false;

	return true;
}