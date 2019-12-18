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
struct o2hb_region {int dummy; } ;
struct o2hb_bio_wait_ctxt {int wc_error; int /*<<< orphan*/  wc_num_reqs; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2hb_bio_wait_init (struct o2hb_bio_wait_ctxt*) ; 
 struct bio* o2hb_setup_one_bio (struct o2hb_region*,struct o2hb_bio_wait_ctxt*,unsigned int*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_wait_on_io (struct o2hb_bio_wait_ctxt*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static int o2hb_read_slots(struct o2hb_region *reg,
			   unsigned int begin_slot,
			   unsigned int max_slots)
{
	unsigned int current_slot = begin_slot;
	int status;
	struct o2hb_bio_wait_ctxt wc;
	struct bio *bio;

	o2hb_bio_wait_init(&wc);

	while(current_slot < max_slots) {
		bio = o2hb_setup_one_bio(reg, &wc, &current_slot, max_slots,
					 REQ_OP_READ, 0);
		if (IS_ERR(bio)) {
			status = PTR_ERR(bio);
			mlog_errno(status);
			goto bail_and_wait;
		}

		atomic_inc(&wc.wc_num_reqs);
		submit_bio(bio);
	}

	status = 0;

bail_and_wait:
	o2hb_wait_on_io(&wc);
	if (wc.wc_error && !status)
		status = wc.wc_error;

	return status;
}