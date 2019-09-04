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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ scsi_stat; } ;
struct TYPE_4__ {TYPE_1__ scsi_rsp; } ;
struct esas2r_request {scalar_t__ req_stat; scalar_t__ timeout; TYPE_2__ func_rsp; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_vda_ob_rsp {int /*<<< orphan*/  func_rsp; } ;

/* Variables and functions */
 scalar_t__ RQ_MAX_TIMEOUT ; 
 scalar_t__ RS_ABORTED ; 
 scalar_t__ RS_SCSI_ERROR ; 
 scalar_t__ RS_SUCCESS ; 
 scalar_t__ RS_TIMEOUT ; 
 scalar_t__ SAM_STAT_CONDITION_MET ; 
 scalar_t__ SAM_STAT_GOOD ; 
 scalar_t__ SAM_STAT_INTERMEDIATE ; 
 scalar_t__ SAM_STAT_INTERMEDIATE_CONDITION_MET ; 
 int /*<<< orphan*/  esas2r_trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void esas2r_handle_outbound_rsp_err(struct esas2r_adapter *a,
					   struct esas2r_request *rq,
					   struct atto_vda_ob_rsp *rsp)
{

	/*
	 * For I/O requests, only copy the response if an error
	 * occurred and setup a callback to do error processing.
	 */
	if (unlikely(rq->req_stat != RS_SUCCESS)) {
		memcpy(&rq->func_rsp, &rsp->func_rsp, sizeof(rsp->func_rsp));

		if (rq->req_stat == RS_ABORTED) {
			if (rq->timeout > RQ_MAX_TIMEOUT)
				rq->req_stat = RS_TIMEOUT;
		} else if (rq->req_stat == RS_SCSI_ERROR) {
			u8 scsistatus = rq->func_rsp.scsi_rsp.scsi_stat;

			esas2r_trace("scsistatus: %x", scsistatus);

			/* Any of these are a good result. */
			if (scsistatus == SAM_STAT_GOOD || scsistatus ==
			    SAM_STAT_CONDITION_MET || scsistatus ==
			    SAM_STAT_INTERMEDIATE || scsistatus ==
			    SAM_STAT_INTERMEDIATE_CONDITION_MET) {
				rq->req_stat = RS_SUCCESS;
				rq->func_rsp.scsi_rsp.scsi_stat =
					SAM_STAT_GOOD;
			}
		}
	}
}