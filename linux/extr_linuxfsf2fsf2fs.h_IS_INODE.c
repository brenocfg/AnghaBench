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
struct f2fs_node {int dummy; } ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int RAW_IS_INODE (struct f2fs_node*) ; 

__attribute__((used)) static inline bool IS_INODE(struct page *page)
{
	struct f2fs_node *p = F2FS_NODE(page);

	return RAW_IS_INODE(p);
}