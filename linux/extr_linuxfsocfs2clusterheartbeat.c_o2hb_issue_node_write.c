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
struct o2hb_bio_wait_ctxt {int /*<<< orphan*/  wc_num_reqs; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2hb_bio_wait_init (struct o2hb_bio_wait_ctxt*) ; 
 struct bio* o2hb_setup_one_bio (struct o2hb_region*,struct o2hb_bio_wait_ctxt*,unsigned int*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int o2nm_this_node () ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static int o2hb_issue_node_write(struct o2hb_region *reg,
				 struct o2hb_bio_wait_ctxt *write_wc)
{
	int status;
	unsigned int slot;
	struct bio *bio;

	o2hb_bio_wait_init(write_wc);

	slot = o2nm_this_node();

	bio = o2hb_setup_one_bio(reg, write_wc, &slot, slot+1, REQ_OP_WRITE,
				 REQ_SYNC);
	if (IS_ERR(bio)) {
		status = PTR_ERR(bio);
		mlog_errno(status);
		goto bail;
	}

	atomic_inc(&write_wc->wc_num_reqs);
	submit_bio(bio);

	status = 0;
bail:
	return status;
}