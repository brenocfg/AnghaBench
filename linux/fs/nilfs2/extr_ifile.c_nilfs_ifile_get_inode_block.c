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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  NILFS_VALID_INODE (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  nilfs_error (struct super_block*,char*,unsigned long) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,int,unsigned long) ; 
 int nilfs_palloc_get_entry_block (struct inode*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_ifile_get_inode_block(struct inode *ifile, ino_t ino,
				struct buffer_head **out_bh)
{
	struct super_block *sb = ifile->i_sb;
	int err;

	if (unlikely(!NILFS_VALID_INODE(sb, ino))) {
		nilfs_error(sb, "bad inode number: %lu", (unsigned long)ino);
		return -EINVAL;
	}

	err = nilfs_palloc_get_entry_block(ifile, ino, 0, out_bh);
	if (unlikely(err))
		nilfs_msg(sb, KERN_WARNING, "error %d reading inode: ino=%lu",
			  err, (unsigned long)ino);
	return err;
}