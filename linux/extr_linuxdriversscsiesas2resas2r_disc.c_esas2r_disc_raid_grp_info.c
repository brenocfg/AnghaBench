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
struct esas2r_request {struct esas2r_disc_context* interrupt_cx; int /*<<< orphan*/  comp_cb; TYPE_3__* vda_rsp_data; } ;
struct esas2r_disc_context {scalar_t__ raid_grp_ix; int /*<<< orphan*/  scan_gen; int /*<<< orphan*/  state; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_vda_grp_info {scalar_t__ grp_index; } ;
struct TYPE_4__ {struct atto_vda_grp_info grp_info; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ mgt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCS_DISC_DONE ; 
 int /*<<< orphan*/  VDAMGT_GRP_INFO ; 
 scalar_t__ VDA_MAX_RAID_GROUPS ; 
 int /*<<< orphan*/  esas2r_build_mgt_req (struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_disc_raid_grp_info_cb ; 
 int esas2r_disc_start_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_rq_init_request (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  memset (struct atto_vda_grp_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool esas2r_disc_raid_grp_info(struct esas2r_adapter *a,
				      struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	bool rslt;
	struct atto_vda_grp_info *grpinfo;

	esas2r_trace_enter();

	esas2r_trace("raid_group_idx: %d", dc->raid_grp_ix);

	if (dc->raid_grp_ix >= VDA_MAX_RAID_GROUPS) {
		dc->state = DCS_DISC_DONE;

		esas2r_trace_exit();

		return false;
	}

	esas2r_rq_init_request(rq, a);

	grpinfo = &rq->vda_rsp_data->mgt_data.data.grp_info;

	memset(grpinfo, 0, sizeof(struct atto_vda_grp_info));

	esas2r_build_mgt_req(a,
			     rq,
			     VDAMGT_GRP_INFO,
			     dc->scan_gen,
			     0,
			     sizeof(struct atto_vda_grp_info),
			     NULL);

	grpinfo->grp_index = dc->raid_grp_ix;

	rq->comp_cb = esas2r_disc_raid_grp_info_cb;

	rq->interrupt_cx = dc;

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_exit();

	return rslt;
}