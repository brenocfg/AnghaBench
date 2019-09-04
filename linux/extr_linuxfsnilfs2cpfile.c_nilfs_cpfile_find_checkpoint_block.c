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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  nilfs_cpfile_first_checkpoint_in_block (struct inode*,unsigned long) ; 
 unsigned long nilfs_cpfile_get_blkoff (struct inode*,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_find_block (struct inode*,unsigned long,unsigned long,unsigned long*,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_cpfile_find_checkpoint_block(struct inode *cpfile,
					      __u64 start_cno, __u64 end_cno,
					      __u64 *cnop,
					      struct buffer_head **bhp)
{
	unsigned long start, end, blkoff;
	int ret;

	if (unlikely(start_cno > end_cno))
		return -ENOENT;

	start = nilfs_cpfile_get_blkoff(cpfile, start_cno);
	end = nilfs_cpfile_get_blkoff(cpfile, end_cno);

	ret = nilfs_mdt_find_block(cpfile, start, end, &blkoff, bhp);
	if (!ret)
		*cnop = (blkoff == start) ? start_cno :
			nilfs_cpfile_first_checkpoint_in_block(cpfile, blkoff);
	return ret;
}