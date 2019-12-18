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
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int f2fs_verity_metadata_pos (struct inode*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *f2fs_read_merkle_tree_page(struct inode *inode,
					       pgoff_t index)
{
	index += f2fs_verity_metadata_pos(inode) >> PAGE_SHIFT;

	return read_mapping_page(inode->i_mapping, index, NULL);
}