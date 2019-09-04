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
struct the_nilfs {int /*<<< orphan*/  ns_blocksize; int /*<<< orphan*/  ns_bdev; } ;
struct buffer_head {unsigned int b_size; scalar_t__ b_blocknr; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,unsigned int) ; 
 struct buffer_head* __bread (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 

__attribute__((used)) static void nilfs_skip_summary_info(struct the_nilfs *nilfs,
				    struct buffer_head **pbh,
				    unsigned int *offset, unsigned int bytes,
				    unsigned long count)
{
	unsigned int rest_item_in_current_block
		= ((*pbh)->b_size - *offset) / bytes;

	if (count <= rest_item_in_current_block) {
		*offset += bytes * count;
	} else {
		sector_t blocknr = (*pbh)->b_blocknr;
		unsigned int nitem_per_block = (*pbh)->b_size / bytes;
		unsigned int bcnt;

		count -= rest_item_in_current_block;
		bcnt = DIV_ROUND_UP(count, nitem_per_block);
		*offset = bytes * (count - (bcnt - 1) * nitem_per_block);

		brelse(*pbh);
		*pbh = __bread(nilfs->ns_bdev, blocknr + bcnt,
			       nilfs->ns_blocksize);
	}
}