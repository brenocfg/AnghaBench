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
struct super_block {scalar_t__ s_blocksize; } ;
struct msdos_sb_info {int cluster_size; unsigned long cluster_bits; scalar_t__ sec_per_clus; } ;
struct msdos_dir_entry {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int MAX_BUF_PER_PAGE ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int fat_alloc_clusters (struct inode*,int*,int) ; 
 scalar_t__ fat_clus_to_blknr (struct msdos_sb_info*,int) ; 
 int /*<<< orphan*/  fat_free_clusters (struct inode*,int) ; 
 int /*<<< orphan*/  fat_make_i_pos (struct super_block*,struct buffer_head*,struct msdos_dir_entry*) ; 
 int fat_zeroed_cluster (struct inode*,scalar_t__,int,struct buffer_head**,int) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,unsigned long) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long min (unsigned long,scalar_t__) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static int fat_add_new_entries(struct inode *dir, void *slots, int nr_slots,
			       int *nr_cluster, struct msdos_dir_entry **de,
			       struct buffer_head **bh, loff_t *i_pos)
{
	struct super_block *sb = dir->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *bhs[MAX_BUF_PER_PAGE];
	sector_t blknr, start_blknr, last_blknr;
	unsigned long size, copy;
	int err, i, n, offset, cluster[2];

	/*
	 * The minimum cluster size is 512bytes, and maximum entry
	 * size is 32*slots (672bytes).  So, iff the cluster size is
	 * 512bytes, we may need two clusters.
	 */
	size = nr_slots * sizeof(struct msdos_dir_entry);
	*nr_cluster = (size + (sbi->cluster_size - 1)) >> sbi->cluster_bits;
	BUG_ON(*nr_cluster > 2);

	err = fat_alloc_clusters(dir, cluster, *nr_cluster);
	if (err)
		goto error;

	/*
	 * First stage: Fill the directory entry.  NOTE: This cluster
	 * is not referenced from any inode yet, so updates order is
	 * not important.
	 */
	i = n = copy = 0;
	do {
		start_blknr = blknr = fat_clus_to_blknr(sbi, cluster[i]);
		last_blknr = start_blknr + sbi->sec_per_clus;
		while (blknr < last_blknr) {
			bhs[n] = sb_getblk(sb, blknr);
			if (!bhs[n]) {
				err = -ENOMEM;
				goto error_nomem;
			}

			/* fill the directory entry */
			copy = min(size, sb->s_blocksize);
			memcpy(bhs[n]->b_data, slots, copy);
			slots += copy;
			size -= copy;
			set_buffer_uptodate(bhs[n]);
			mark_buffer_dirty_inode(bhs[n], dir);
			if (!size)
				break;
			n++;
			blknr++;
		}
	} while (++i < *nr_cluster);

	memset(bhs[n]->b_data + copy, 0, sb->s_blocksize - copy);
	offset = copy - sizeof(struct msdos_dir_entry);
	get_bh(bhs[n]);
	*bh = bhs[n];
	*de = (struct msdos_dir_entry *)((*bh)->b_data + offset);
	*i_pos = fat_make_i_pos(sb, *bh, *de);

	/* Second stage: clear the rest of cluster, and write outs */
	err = fat_zeroed_cluster(dir, start_blknr, ++n, bhs, MAX_BUF_PER_PAGE);
	if (err)
		goto error_free;

	return cluster[0];

error_free:
	brelse(*bh);
	*bh = NULL;
	n = 0;
error_nomem:
	for (i = 0; i < n; i++)
		bforget(bhs[i]);
	fat_free_clusters(dir, cluster[0]);
error:
	return err;
}