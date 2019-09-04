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
struct buffer_info {int /*<<< orphan*/  bi_position; scalar_t__ bi_parent; int /*<<< orphan*/ * bi_bh; } ;
struct block_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ dc_size; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* B_N_CHILD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CHILD_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RFALSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_blkh_free_space (struct block_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blkh_nr_item (struct block_head*,int /*<<< orphan*/ ) ; 

void make_empty_node(struct buffer_info *bi)
{
	struct block_head *blkh;

	RFALSE(bi->bi_bh == NULL, "PAP-12295: pointer to the buffer is NULL");

	blkh = B_BLK_HEAD(bi->bi_bh);
	set_blkh_nr_item(blkh, 0);
	set_blkh_free_space(blkh, MAX_CHILD_SIZE(bi->bi_bh));

	if (bi->bi_parent)
		B_N_CHILD(bi->bi_parent, bi->bi_position)->dc_size = 0;	/* Endian safe if 0 */
}