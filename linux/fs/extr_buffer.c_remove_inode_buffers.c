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
struct list_head {int /*<<< orphan*/  next; } ;
struct address_space {int /*<<< orphan*/  private_lock; struct address_space* private_data; struct list_head private_list; } ;
struct inode {struct address_space i_data; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct buffer_head* BH_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __remove_assoc_queue (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ inode_has_buffers (struct inode*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int remove_inode_buffers(struct inode *inode)
{
	int ret = 1;

	if (inode_has_buffers(inode)) {
		struct address_space *mapping = &inode->i_data;
		struct list_head *list = &mapping->private_list;
		struct address_space *buffer_mapping = mapping->private_data;

		spin_lock(&buffer_mapping->private_lock);
		while (!list_empty(list)) {
			struct buffer_head *bh = BH_ENTRY(list->next);
			if (buffer_dirty(bh)) {
				ret = 0;
				break;
			}
			__remove_assoc_queue(bh);
		}
		spin_unlock(&buffer_mapping->private_lock);
	}
	return ret;
}