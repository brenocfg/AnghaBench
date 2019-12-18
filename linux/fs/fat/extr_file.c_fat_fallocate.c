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
struct super_block {int dummy; } ;
struct msdos_sb_info {int cluster_size; int cluster_bits; } ;
struct inode {int i_blocks; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int fat_add_cluster (struct inode*) ; 
 int fat_cont_expand (struct inode*,int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static long fat_fallocate(struct file *file, int mode,
			  loff_t offset, loff_t len)
{
	int nr_cluster; /* Number of clusters to be allocated */
	loff_t mm_bytes; /* Number of bytes to be allocated for file */
	loff_t ondisksize; /* block aligned on-disk size in bytes*/
	struct inode *inode = file->f_mapping->host;
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	int err = 0;

	/* No support for hole punch or other fallocate flags. */
	if (mode & ~FALLOC_FL_KEEP_SIZE)
		return -EOPNOTSUPP;

	/* No support for dir */
	if (!S_ISREG(inode->i_mode))
		return -EOPNOTSUPP;

	inode_lock(inode);
	if (mode & FALLOC_FL_KEEP_SIZE) {
		ondisksize = inode->i_blocks << 9;
		if ((offset + len) <= ondisksize)
			goto error;

		/* First compute the number of clusters to be allocated */
		mm_bytes = offset + len - ondisksize;
		nr_cluster = (mm_bytes + (sbi->cluster_size - 1)) >>
			sbi->cluster_bits;

		/* Start the allocation.We are not zeroing out the clusters */
		while (nr_cluster-- > 0) {
			err = fat_add_cluster(inode);
			if (err)
				goto error;
		}
	} else {
		if ((offset + len) <= i_size_read(inode))
			goto error;

		/* This is just an expanding truncate */
		err = fat_cont_expand(inode, (offset + len));
	}

error:
	inode_unlock(inode);
	return err;
}