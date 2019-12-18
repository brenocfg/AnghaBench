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
struct bio_post_read_ctx {int /*<<< orphan*/  cur_step; } ;
struct bio {struct bio_post_read_ctx* bi_private; int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  F2FS_P_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAULT_READ_IO ; 
 int /*<<< orphan*/  STEP_INITIAL ; 
 int /*<<< orphan*/  __read_end_io (struct bio*) ; 
 int /*<<< orphan*/  bio_first_page_all (struct bio*) ; 
 int /*<<< orphan*/  bio_post_read_processing (struct bio_post_read_ctx*) ; 
 scalar_t__ f2fs_bio_post_read_required (struct bio*) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_read_end_io(struct bio *bio)
{
	if (time_to_inject(F2FS_P_SB(bio_first_page_all(bio)),
						FAULT_READ_IO)) {
		f2fs_show_injection_info(FAULT_READ_IO);
		bio->bi_status = BLK_STS_IOERR;
	}

	if (f2fs_bio_post_read_required(bio)) {
		struct bio_post_read_ctx *ctx = bio->bi_private;

		ctx->cur_step = STEP_INITIAL;
		bio_post_read_processing(ctx);
		return;
	}

	__read_end_io(bio);
}