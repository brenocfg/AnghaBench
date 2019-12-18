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
struct writeback_control {int dummy; } ;
struct buffer_head {int b_blocknr; int b_size; int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_end_io; } ;
struct TYPE_2__ {int bi_sector; int bi_size; } ;
struct bio {int bi_write_hint; struct buffer_head* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  enum rw_hint { ____Placeholder_rw_hint } rw_hint ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_META ; 
 int REQ_OP_WRITE ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_meta (struct buffer_head*) ; 
 scalar_t__ buffer_prio (struct buffer_head*) ; 
 int buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  end_bio_bh_io_sync ; 
 int /*<<< orphan*/  guard_bio_eod (int,struct bio*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ test_set_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  wbc_account_cgroup_owner (struct writeback_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wbc_init_bio (struct writeback_control*,struct bio*) ; 

__attribute__((used)) static int submit_bh_wbc(int op, int op_flags, struct buffer_head *bh,
			 enum rw_hint write_hint, struct writeback_control *wbc)
{
	struct bio *bio;

	BUG_ON(!buffer_locked(bh));
	BUG_ON(!buffer_mapped(bh));
	BUG_ON(!bh->b_end_io);
	BUG_ON(buffer_delay(bh));
	BUG_ON(buffer_unwritten(bh));

	/*
	 * Only clear out a write error when rewriting
	 */
	if (test_set_buffer_req(bh) && (op == REQ_OP_WRITE))
		clear_buffer_write_io_error(bh);

	/*
	 * from here on down, it's all bio -- do the initial mapping,
	 * submit_bio -> generic_make_request may further map this bio around
	 */
	bio = bio_alloc(GFP_NOIO, 1);

	bio->bi_iter.bi_sector = bh->b_blocknr * (bh->b_size >> 9);
	bio_set_dev(bio, bh->b_bdev);
	bio->bi_write_hint = write_hint;

	bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh));
	BUG_ON(bio->bi_iter.bi_size != bh->b_size);

	bio->bi_end_io = end_bio_bh_io_sync;
	bio->bi_private = bh;

	/* Take care of bh's that straddle the end of the device */
	guard_bio_eod(op, bio);

	if (buffer_meta(bh))
		op_flags |= REQ_META;
	if (buffer_prio(bh))
		op_flags |= REQ_PRIO;
	bio_set_op_attrs(bio, op, op_flags);

	if (wbc) {
		wbc_init_bio(wbc, bio);
		wbc_account_cgroup_owner(wbc, bh->b_page, bh->b_size);
	}

	submit_bio(bio);
	return 0;
}