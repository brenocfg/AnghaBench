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
struct f2fs_inode {int /*<<< orphan*/  i_inode_checksum; } ;
struct TYPE_2__ {struct f2fs_inode i; } ;

/* Variables and functions */
 TYPE_1__* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_enable_inode_chksum (struct f2fs_sb_info*,struct page*) ; 
 int /*<<< orphan*/  f2fs_inode_chksum (struct f2fs_sb_info*,struct page*) ; 

void f2fs_inode_chksum_set(struct f2fs_sb_info *sbi, struct page *page)
{
	struct f2fs_inode *ri = &F2FS_NODE(page)->i;

	if (!f2fs_enable_inode_chksum(sbi, page))
		return;

	ri->i_inode_checksum = cpu_to_le32(f2fs_inode_chksum(sbi, page));
}