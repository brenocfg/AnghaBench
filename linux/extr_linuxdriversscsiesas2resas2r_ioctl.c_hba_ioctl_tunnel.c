#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct esas2r_sg_context {int /*<<< orphan*/  length; } ;
struct esas2r_request {TYPE_2__* vrq; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_ioctl {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  sge; } ;
struct TYPE_4__ {TYPE_1__ ioctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTO_STS_OUT_OF_RSRC ; 
 int /*<<< orphan*/  VDA_IOCTL_HBA ; 
 int /*<<< orphan*/  esas2r_build_ioctl_req (struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_build_sg_list (struct esas2r_adapter*,struct esas2r_request*,struct esas2r_sg_context*) ; 
 int /*<<< orphan*/  esas2r_sgc_init (struct esas2r_sg_context*,struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_start_request (struct esas2r_adapter*,struct esas2r_request*) ; 

__attribute__((used)) static bool hba_ioctl_tunnel(struct esas2r_adapter *a,
			     struct atto_ioctl *hi,
			     struct esas2r_request *rq,
			     struct esas2r_sg_context *sgc)
{
	esas2r_sgc_init(sgc, a, rq, rq->vrq->ioctl.sge);

	esas2r_build_ioctl_req(a, rq, sgc->length, VDA_IOCTL_HBA);

	if (!esas2r_build_sg_list(a, rq, sgc)) {
		hi->status = ATTO_STS_OUT_OF_RSRC;

		return false;
	}

	esas2r_start_request(a, rq);

	return true;
}