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
 size_t DEF_ADDRS_PER_INODE ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 size_t get_inline_xattr_addrs (struct inode*) ; 

__attribute__((used)) static inline void *inline_xattr_addr(struct inode *inode, struct page *page)
{
	struct f2fs_inode *ri = F2FS_INODE(page);

	return (void *)&(ri->i_addr[DEF_ADDRS_PER_INODE -
					get_inline_xattr_addrs(inode)]);
}