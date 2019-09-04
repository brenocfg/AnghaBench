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
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int s_cluster_bits; int s_cluster_ratio; } ;
struct buffer_head {unsigned int b_size; struct buffer_head* b_this_page; } ;
typedef  unsigned int ext4_fsblk_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_NUM_B2C (struct ext4_sb_info*,int) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_da_release_space (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_es_remove_extent (struct inode*,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_find_delalloc_cluster (struct inode*,unsigned int) ; 
 struct buffer_head* page_buffers (struct page*) ; 

__attribute__((used)) static void ext4_da_page_release_reservation(struct page *page,
					     unsigned int offset,
					     unsigned int length)
{
	int to_release = 0, contiguous_blks = 0;
	struct buffer_head *head, *bh;
	unsigned int curr_off = 0;
	struct inode *inode = page->mapping->host;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	unsigned int stop = offset + length;
	int num_clusters;
	ext4_fsblk_t lblk;

	BUG_ON(stop > PAGE_SIZE || stop < length);

	head = page_buffers(page);
	bh = head;
	do {
		unsigned int next_off = curr_off + bh->b_size;

		if (next_off > stop)
			break;

		if ((offset <= curr_off) && (buffer_delay(bh))) {
			to_release++;
			contiguous_blks++;
			clear_buffer_delay(bh);
		} else if (contiguous_blks) {
			lblk = page->index <<
			       (PAGE_SHIFT - inode->i_blkbits);
			lblk += (curr_off >> inode->i_blkbits) -
				contiguous_blks;
			ext4_es_remove_extent(inode, lblk, contiguous_blks);
			contiguous_blks = 0;
		}
		curr_off = next_off;
	} while ((bh = bh->b_this_page) != head);

	if (contiguous_blks) {
		lblk = page->index << (PAGE_SHIFT - inode->i_blkbits);
		lblk += (curr_off >> inode->i_blkbits) - contiguous_blks;
		ext4_es_remove_extent(inode, lblk, contiguous_blks);
	}

	/* If we have released all the blocks belonging to a cluster, then we
	 * need to release the reserved space for that cluster. */
	num_clusters = EXT4_NUM_B2C(sbi, to_release);
	while (num_clusters > 0) {
		lblk = (page->index << (PAGE_SHIFT - inode->i_blkbits)) +
			((num_clusters - 1) << sbi->s_cluster_bits);
		if (sbi->s_cluster_ratio == 1 ||
		    !ext4_find_delalloc_cluster(inode, lblk))
			ext4_da_release_space(inode, 1);

		num_clusters--;
	}
}