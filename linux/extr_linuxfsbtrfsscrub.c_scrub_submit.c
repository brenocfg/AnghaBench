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
struct scrub_ctx {int curr; struct scrub_bio** bios; } ;
struct scrub_bio {int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfsic_submit_bio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scrub_pending_bio_inc (struct scrub_ctx*) ; 

__attribute__((used)) static void scrub_submit(struct scrub_ctx *sctx)
{
	struct scrub_bio *sbio;

	if (sctx->curr == -1)
		return;

	sbio = sctx->bios[sctx->curr];
	sctx->curr = -1;
	scrub_pending_bio_inc(sctx);
	btrfsic_submit_bio(sbio->bio);
}