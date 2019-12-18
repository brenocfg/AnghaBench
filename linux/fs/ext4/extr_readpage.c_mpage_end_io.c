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
struct bio {struct bio_post_read_ctx* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  STEP_INITIAL ; 
 int /*<<< orphan*/  __read_end_io (struct bio*) ; 
 int /*<<< orphan*/  bio_post_read_processing (struct bio_post_read_ctx*) ; 
 scalar_t__ bio_post_read_required (struct bio*) ; 

__attribute__((used)) static void mpage_end_io(struct bio *bio)
{
	if (bio_post_read_required(bio)) {
		struct bio_post_read_ctx *ctx = bio->bi_private;

		ctx->cur_step = STEP_INITIAL;
		bio_post_read_processing(ctx);
		return;
	}
	__read_end_io(bio);
}