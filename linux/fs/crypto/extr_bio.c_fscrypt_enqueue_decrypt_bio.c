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
struct fscrypt_ctx {int /*<<< orphan*/  work; struct bio* bio; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion_pages ; 
 int /*<<< orphan*/  fscrypt_enqueue_decrypt_work (int /*<<< orphan*/ *) ; 

void fscrypt_enqueue_decrypt_bio(struct fscrypt_ctx *ctx, struct bio *bio)
{
	INIT_WORK(&ctx->work, completion_pages);
	ctx->bio = bio;
	fscrypt_enqueue_decrypt_work(&ctx->work);
}