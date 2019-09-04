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
typedef  union atto_ioctl_csmi {int dummy; } atto_ioctl_csmi ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct esas2r_sg_context {int /*<<< orphan*/  length; } ;
struct esas2r_request {int /*<<< orphan*/  comp_cb; int /*<<< orphan*/  aux_req_cb; union atto_ioctl_csmi* aux_req_cx; TYPE_3__* vrq; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {scalar_t__ lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  ctrl_code; } ;
struct atto_vda_ioctl_req {TYPE_1__ csmi; int /*<<< orphan*/  sge; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__ scsi; struct atto_vda_ioctl_req ioctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  VDA_IOCTL_CSMI ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_build_ioctl_req (struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_build_sg_list (struct esas2r_adapter*,struct esas2r_request*,struct esas2r_sg_context*) ; 
 int /*<<< orphan*/  esas2r_csmi_ioctl_tunnel_comp_cb ; 
 int /*<<< orphan*/  esas2r_sgc_init (struct esas2r_sg_context*,struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_start_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool csmi_ioctl_tunnel(struct esas2r_adapter *a,
			      union atto_ioctl_csmi *ci,
			      struct esas2r_request *rq,
			      struct esas2r_sg_context *sgc,
			      u32 ctrl_code,
			      u16 target_id)
{
	struct atto_vda_ioctl_req *ioctl = &rq->vrq->ioctl;

	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		return false;

	esas2r_sgc_init(sgc, a, rq, rq->vrq->ioctl.sge);
	esas2r_build_ioctl_req(a, rq, sgc->length, VDA_IOCTL_CSMI);
	ioctl->csmi.ctrl_code = cpu_to_le32(ctrl_code);
	ioctl->csmi.target_id = cpu_to_le16(target_id);
	ioctl->csmi.lun = (u8)le32_to_cpu(rq->vrq->scsi.flags);

	/*
	 * Always usurp the completion callback since the interrupt callback
	 * mechanism may be used.
	 */
	rq->aux_req_cx = ci;
	rq->aux_req_cb = rq->comp_cb;
	rq->comp_cb = esas2r_csmi_ioctl_tunnel_comp_cb;

	if (!esas2r_build_sg_list(a, rq, sgc))
		return false;

	esas2r_start_request(a, rq);
	return true;
}