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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  unsigned long __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  i_bmap; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* NILFS_I (struct inode*) ; 
 unsigned long ULONG_MAX ; 
 int nilfs_bmap_seek_key (int /*<<< orphan*/ ,unsigned long,unsigned long*) ; 
 int nilfs_mdt_read_block (struct inode*,unsigned long,int,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_mdt_find_block(struct inode *inode, unsigned long start,
			 unsigned long end, unsigned long *blkoff,
			 struct buffer_head **out_bh)
{
	__u64 next;
	int ret;

	if (unlikely(start > end))
		return -ENOENT;

	ret = nilfs_mdt_read_block(inode, start, true, out_bh);
	if (!ret) {
		*blkoff = start;
		goto out;
	}
	if (unlikely(ret != -ENOENT || start == ULONG_MAX))
		goto out;

	ret = nilfs_bmap_seek_key(NILFS_I(inode)->i_bmap, start + 1, &next);
	if (!ret) {
		if (next <= end) {
			ret = nilfs_mdt_read_block(inode, next, true, out_bh);
			if (!ret)
				*blkoff = next;
		} else {
			ret = -ENOENT;
		}
	}
out:
	return ret;
}