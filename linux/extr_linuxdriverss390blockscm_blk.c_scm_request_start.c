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
struct scm_request {int /*<<< orphan*/  aob; struct scm_blk_dev* bdev; } ;
struct scm_blk_dev {int /*<<< orphan*/  queued_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_LOG (int,char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ eadm_start_aob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scm_request_requeue (struct scm_request*) ; 

__attribute__((used)) static void scm_request_start(struct scm_request *scmrq)
{
	struct scm_blk_dev *bdev = scmrq->bdev;

	atomic_inc(&bdev->queued_reqs);
	if (eadm_start_aob(scmrq->aob)) {
		SCM_LOG(5, "no subchannel");
		scm_request_requeue(scmrq);
	}
}