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
struct scrub_ctx {struct scrub_bio* wr_curr_bio; } ;
struct scrub_bio {TYPE_1__* bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfsic_submit_bio (TYPE_1__*) ; 
 int /*<<< orphan*/  scrub_pending_bio_inc (struct scrub_ctx*) ; 

__attribute__((used)) static void scrub_wr_submit(struct scrub_ctx *sctx)
{
	struct scrub_bio *sbio;

	if (!sctx->wr_curr_bio)
		return;

	sbio = sctx->wr_curr_bio;
	sctx->wr_curr_bio = NULL;
	WARN_ON(!sbio->bio->bi_disk);
	scrub_pending_bio_inc(sctx);
	/* process all writes in a single worker thread. Then the block layer
	 * orders the requests before sending them to the driver which
	 * doubled the write performance on spinning disks when measured
	 * with Linux 3.5 */
	btrfsic_submit_bio(sbio->bio);
}