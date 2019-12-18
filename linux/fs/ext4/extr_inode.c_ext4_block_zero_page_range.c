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
struct inode {TYPE_1__* i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 scalar_t__ IS_DAX (struct inode*) ; 
 int PAGE_SIZE ; 
 int __ext4_block_zero_page_range (int /*<<< orphan*/ *,struct address_space*,int,int) ; 
 int /*<<< orphan*/  ext4_iomap_ops ; 
 int iomap_zero_range (struct inode*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_block_zero_page_range(handle_t *handle,
		struct address_space *mapping, loff_t from, loff_t length)
{
	struct inode *inode = mapping->host;
	unsigned offset = from & (PAGE_SIZE-1);
	unsigned blocksize = inode->i_sb->s_blocksize;
	unsigned max = blocksize - (offset & (blocksize - 1));

	/*
	 * correct length if it does not fall between
	 * 'from' and the end of the block
	 */
	if (length > max || length < 0)
		length = max;

	if (IS_DAX(inode)) {
		return iomap_zero_range(inode, from, length, NULL,
					&ext4_iomap_ops);
	}
	return __ext4_block_zero_page_range(handle, mapping, from, length);
}