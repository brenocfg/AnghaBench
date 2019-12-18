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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EBADE ; 
 int EINVAL ; 
 unsigned int REMAP_FILE_CAN_SHORTEN ; 
 unsigned int REMAP_FILE_DEDUP ; 
 scalar_t__ i_blocksize (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static int generic_remap_check_len(struct inode *inode_in,
				   struct inode *inode_out,
				   loff_t pos_out,
				   loff_t *len,
				   unsigned int remap_flags)
{
	u64 blkmask = i_blocksize(inode_in) - 1;
	loff_t new_len = *len;

	if ((*len & blkmask) == 0)
		return 0;

	if ((remap_flags & REMAP_FILE_DEDUP) ||
	    pos_out + *len < i_size_read(inode_out))
		new_len &= ~blkmask;

	if (new_len == *len)
		return 0;

	if (remap_flags & REMAP_FILE_CAN_SHORTEN) {
		*len = new_len;
		return 0;
	}

	return (remap_flags & REMAP_FILE_DEDUP) ? -EBADE : -EINVAL;
}