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
struct bio_post_read_ctx {int cur_step; int enabled_steps; int /*<<< orphan*/  bio; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  STEP_DECRYPT 128 
 int /*<<< orphan*/  __read_end_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrypt_work ; 
 int /*<<< orphan*/  fscrypt_enqueue_decrypt_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bio_post_read_processing(struct bio_post_read_ctx *ctx)
{
	switch (++ctx->cur_step) {
	case STEP_DECRYPT:
		if (ctx->enabled_steps & (1 << STEP_DECRYPT)) {
			INIT_WORK(&ctx->work, decrypt_work);
			fscrypt_enqueue_decrypt_work(&ctx->work);
			return;
		}
		ctx->cur_step++;
		/* fall-through */
	default:
		__read_end_io(ctx->bio);
	}
}