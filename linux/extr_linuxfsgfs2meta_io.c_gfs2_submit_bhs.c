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
struct buffer_head {int b_blocknr; int b_size; int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_bdev; } ;
struct TYPE_2__ {int bi_sector; scalar_t__ bi_size; } ;
struct bio {int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int /*<<< orphan*/  gfs2_meta_read_endio ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void gfs2_submit_bhs(int op, int op_flags, struct buffer_head *bhs[],
			    int num)
{
	while (num > 0) {
		struct buffer_head *bh = *bhs;
		struct bio *bio;

		bio = bio_alloc(GFP_NOIO, num);
		bio->bi_iter.bi_sector = bh->b_blocknr * (bh->b_size >> 9);
		bio_set_dev(bio, bh->b_bdev);
		while (num > 0) {
			bh = *bhs;
			if (!bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh))) {
				BUG_ON(bio->bi_iter.bi_size == 0);
				break;
			}
			bhs++;
			num--;
		}
		bio->bi_end_io = gfs2_meta_read_endio;
		bio_set_op_attrs(bio, op, op_flags);
		submit_bio(bio);
	}
}