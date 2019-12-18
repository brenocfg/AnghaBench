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
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;
struct f2fs_node {TYPE_1__ footer; } ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  f2fs_inode_chksum_set (int /*<<< orphan*/ ,struct page*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_mark(struct page *page, int mark, int type)
{
	struct f2fs_node *rn = F2FS_NODE(page);
	unsigned int flag = le32_to_cpu(rn->footer.flag);
	if (mark)
		flag |= (0x1 << type);
	else
		flag &= ~(0x1 << type);
	rn->footer.flag = cpu_to_le32(flag);

#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_P_SB(page), page);
#endif
}