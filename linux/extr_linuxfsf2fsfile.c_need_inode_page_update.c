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
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_MAPPING (struct f2fs_sb_info*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ f2fs_need_inode_block_update (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool need_inode_page_update(struct f2fs_sb_info *sbi, nid_t ino)
{
	struct page *i = find_get_page(NODE_MAPPING(sbi), ino);
	bool ret = false;
	/* But we need to avoid that there are some inode updates */
	if ((i && PageDirty(i)) || f2fs_need_inode_block_update(sbi, ino))
		ret = true;
	f2fs_put_page(i, 0);
	return ret;
}