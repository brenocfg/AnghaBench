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
struct page {int /*<<< orphan*/  _refcount; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ___wait_var_event (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct page* dax_layout_busy_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_wait_dax_page (struct ext4_inode_info*) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 

int ext4_break_layouts(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct page *page;
	int error;

	if (WARN_ON_ONCE(!rwsem_is_locked(&ei->i_mmap_sem)))
		return -EINVAL;

	do {
		page = dax_layout_busy_page(inode->i_mapping);
		if (!page)
			return 0;

		error = ___wait_var_event(&page->_refcount,
				atomic_read(&page->_refcount) == 1,
				TASK_INTERRUPTIBLE, 0, 0,
				ext4_wait_dax_page(ei));
	} while (error == 0);

	return error;
}