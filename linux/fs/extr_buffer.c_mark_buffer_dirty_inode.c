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
struct inode {struct address_space* i_mapping; } ;
struct buffer_head {struct address_space* b_assoc_map; int /*<<< orphan*/  b_assoc_buffers; TYPE_1__* b_page; } ;
struct address_space {int /*<<< orphan*/  private_lock; int /*<<< orphan*/  private_list; struct address_space* private_data; } ;
struct TYPE_2__ {struct address_space* mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mark_buffer_dirty_inode(struct buffer_head *bh, struct inode *inode)
{
	struct address_space *mapping = inode->i_mapping;
	struct address_space *buffer_mapping = bh->b_page->mapping;

	mark_buffer_dirty(bh);
	if (!mapping->private_data) {
		mapping->private_data = buffer_mapping;
	} else {
		BUG_ON(mapping->private_data != buffer_mapping);
	}
	if (!bh->b_assoc_map) {
		spin_lock(&buffer_mapping->private_lock);
		list_move_tail(&bh->b_assoc_buffers,
				&mapping->private_list);
		bh->b_assoc_map = mapping;
		spin_unlock(&buffer_mapping->private_lock);
	}
}