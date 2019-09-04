#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dev_index; int /*<<< orphan*/  scan_generation; } ;
struct TYPE_10__ {TYPE_4__ mgt_rsp; } ;
struct esas2r_request {scalar_t__ req_stat; TYPE_5__ func_rsp; TYPE_3__* vda_rsp_data; scalar_t__ interrupt_cx; } ;
struct esas2r_disc_context {int dev_ix; int curr_virt_id; int curr_phys_id; int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  dev_addr_type; int /*<<< orphan*/  scan_gen; } ;
struct esas2r_adapter {int /*<<< orphan*/  mem_lock; } ;
struct atto_vda_devinfo {int /*<<< orphan*/  phys_target_id; int /*<<< orphan*/  features; int /*<<< orphan*/  target_id; } ;
struct TYPE_6__ {struct atto_vda_devinfo dev_info; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_8__ {TYPE_2__ mgt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTO_GDA_AT_PORT ; 
 int DCF_POLLED ; 
 int /*<<< orphan*/  DCS_DISC_DONE ; 
 int /*<<< orphan*/  DCS_PT_DEV_ADDR ; 
 int /*<<< orphan*/  DCS_PT_DEV_INFO ; 
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
 scalar_t__ RS_DEV_INVALID ; 
 scalar_t__ RS_SCAN_GEN ; 
 scalar_t__ RS_SUCCESS ; 
 int VDADEVFEAT_PHYS_ID ; 
 int /*<<< orphan*/  esas2r_disc_continue (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_rq_destroy_request (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void esas2r_disc_passthru_dev_info_cb(struct esas2r_adapter *a,
					     struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	unsigned long flags;
	struct atto_vda_devinfo *devinfo;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	if (rq->req_stat == RS_SCAN_GEN) {
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;
		dc->dev_ix = 0;
		dc->state = DCS_PT_DEV_INFO;
	} else if (rq->req_stat == RS_SUCCESS) {
		devinfo = &rq->vda_rsp_data->mgt_data.data.dev_info;

		dc->dev_ix = le16_to_cpu(rq->func_rsp.mgt_rsp.dev_index);

		dc->curr_virt_id = le16_to_cpu(devinfo->target_id);

		if (le16_to_cpu(devinfo->features) & VDADEVFEAT_PHYS_ID) {
			dc->curr_phys_id =
				le16_to_cpu(devinfo->phys_target_id);
			dc->dev_addr_type = ATTO_GDA_AT_PORT;
			dc->state = DCS_PT_DEV_ADDR;

			esas2r_trace("curr_virt_id: %d", dc->curr_virt_id);
			esas2r_trace("curr_phys_id: %d", dc->curr_phys_id);
		} else {
			dc->dev_ix++;
		}
	} else {
		if (!(rq->req_stat == RS_DEV_INVALID)) {
			esas2r_log(ESAS2R_LOG_WARN,
				   "A request for device information failed - "
				   "status:%d", rq->req_stat);
		}

		dc->state = DCS_DISC_DONE;
	}

	esas2r_rq_destroy_request(rq, a);

	/* continue discovery if it's interrupt driven */

	if (!(dc->flags & DCF_POLLED))
		esas2r_disc_continue(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_exit();
}