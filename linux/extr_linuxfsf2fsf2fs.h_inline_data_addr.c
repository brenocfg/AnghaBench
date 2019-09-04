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
struct inode {int dummy; } ;
struct f2fs_inode {int /*<<< orphan*/ * i_addr; } ;

/* Variables and functions */
 int DEF_INLINE_RESERVED_SIZE ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int get_extra_isize (struct inode*) ; 

__attribute__((used)) static inline void *inline_data_addr(struct inode *inode, struct page *page)
{
	struct f2fs_inode *ri = F2FS_INODE(page);
	int extra_size = get_extra_isize(inode);

	return (void *)&(ri->i_addr[extra_size + DEF_INLINE_RESERVED_SIZE]);
}