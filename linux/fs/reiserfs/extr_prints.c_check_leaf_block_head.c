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
struct buffer_head {int b_size; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 int BLKH_SIZE ; 
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 int IH_SIZE ; 
 int blkh_free_space (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ *,char*,char*,struct buffer_head*) ; 

__attribute__((used)) static void check_leaf_block_head(struct buffer_head *bh)
{
	struct block_head *blkh;
	int nr;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	if (nr > (bh->b_size - BLKH_SIZE) / IH_SIZE)
		reiserfs_panic(NULL, "vs-6010", "invalid item number %z",
			       bh);
	if (blkh_free_space(blkh) > bh->b_size - BLKH_SIZE - IH_SIZE * nr)
		reiserfs_panic(NULL, "vs-6020", "invalid free space %z",
			       bh);

}