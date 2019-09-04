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
struct scsi_device {struct rdac_dh_data* handler_data; } ;
struct request {int /*<<< orphan*/  rq_flags; } ;
struct rdac_dh_data {scalar_t__ state; } ;

/* Variables and functions */
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 scalar_t__ RDAC_STATE_ACTIVE ; 
 int /*<<< orphan*/  RQF_QUIET ; 

__attribute__((used)) static int rdac_prep_fn(struct scsi_device *sdev, struct request *req)
{
	struct rdac_dh_data *h = sdev->handler_data;
	int ret = BLKPREP_OK;

	if (h->state != RDAC_STATE_ACTIVE) {
		ret = BLKPREP_KILL;
		req->rq_flags |= RQF_QUIET;
	}
	return ret;

}