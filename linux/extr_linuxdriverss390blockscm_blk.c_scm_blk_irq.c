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
struct scm_request {int /*<<< orphan*/  retries; scalar_t__ error; } ;
struct scm_device {int dummy; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  __scmrq_log_error (struct scm_request*) ; 
 int /*<<< orphan*/  scm_blk_handle_error (struct scm_request*) ; 
 int /*<<< orphan*/  scm_request_finish (struct scm_request*) ; 

void scm_blk_irq(struct scm_device *scmdev, void *data, blk_status_t error)
{
	struct scm_request *scmrq = data;

	scmrq->error = error;
	if (error) {
		__scmrq_log_error(scmrq);
		if (scmrq->retries-- > 0) {
			scm_blk_handle_error(scmrq);
			return;
		}
	}

	scm_request_finish(scmrq);
}