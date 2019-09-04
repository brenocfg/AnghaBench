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
struct o2hb_bio_wait_ctxt {int /*<<< orphan*/  wc_error; } ;
struct bio {scalar_t__ bi_status; struct o2hb_bio_wait_ctxt* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  o2hb_bio_wait_dec (struct o2hb_bio_wait_ctxt*,int) ; 

__attribute__((used)) static void o2hb_bio_end_io(struct bio *bio)
{
	struct o2hb_bio_wait_ctxt *wc = bio->bi_private;

	if (bio->bi_status) {
		mlog(ML_ERROR, "IO Error %d\n", bio->bi_status);
		wc->wc_error = blk_status_to_errno(bio->bi_status);
	}

	o2hb_bio_wait_dec(wc, 1);
	bio_put(bio);
}