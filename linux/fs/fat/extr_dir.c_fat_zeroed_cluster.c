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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ sec_per_clus; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int fat_sync_bhs (struct buffer_head**,int) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int fat_zeroed_cluster(struct inode *dir, sector_t blknr, int nr_used,
			      struct buffer_head **bhs, int nr_bhs)
{
	struct super_block *sb = dir->i_sb;
	sector_t last_blknr = blknr + MSDOS_SB(sb)->sec_per_clus;
	int err, i, n;

	/* Zeroing the unused blocks on this cluster */
	blknr += nr_used;
	n = nr_used;
	while (blknr < last_blknr) {
		bhs[n] = sb_getblk(sb, blknr);
		if (!bhs[n]) {
			err = -ENOMEM;
			goto error;
		}
		/* Avoid race with userspace read via bdev */
		lock_buffer(bhs[n]);
		memset(bhs[n]->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bhs[n]);
		unlock_buffer(bhs[n]);
		mark_buffer_dirty_inode(bhs[n], dir);

		n++;
		blknr++;
		if (n == nr_bhs) {
			if (IS_DIRSYNC(dir)) {
				err = fat_sync_bhs(bhs, n);
				if (err)
					goto error;
			}
			for (i = 0; i < n; i++)
				brelse(bhs[i]);
			n = 0;
		}
	}
	if (IS_DIRSYNC(dir)) {
		err = fat_sync_bhs(bhs, n);
		if (err)
			goto error;
	}
	for (i = 0; i < n; i++)
		brelse(bhs[i]);

	return 0;

error:
	for (i = 0; i < n; i++)
		bforget(bhs[i]);
	return err;
}