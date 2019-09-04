#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_ct_els {scalar_t__ status; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_3__ ctels_reply; } ;
struct fc_bsg_reply {int /*<<< orphan*/  reply_payload_rcv_len; int /*<<< orphan*/  result; TYPE_2__ reply_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {TYPE_1__ reply_payload; struct fc_bsg_reply* reply; struct zfcp_fsf_ct_els* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FC_CTELS_STATUS_OK ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_ct_els_job_handler(void *data)
{
	struct bsg_job *job = data;
	struct zfcp_fsf_ct_els *zfcp_ct_els = job->dd_data;
	struct fc_bsg_reply *jr = job->reply;

	jr->reply_payload_rcv_len = job->reply_payload.payload_len;
	jr->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	jr->result = zfcp_ct_els->status ? -EIO : 0;
	bsg_job_done(job, jr->result, jr->reply_payload_rcv_len);
}