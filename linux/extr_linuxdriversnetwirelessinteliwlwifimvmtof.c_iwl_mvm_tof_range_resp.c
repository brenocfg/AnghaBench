#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_tof_range_rsp_ntfy {int /*<<< orphan*/  request_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_range_request; int /*<<< orphan*/  range_resp; } ;
struct iwl_mvm {TYPE_1__ tof_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_MVM_TOF_RANGE_REQ_MAX_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iwl_tof_range_rsp_ntfy*,int) ; 

__attribute__((used)) static int iwl_mvm_tof_range_resp(struct iwl_mvm *mvm, void *data)
{
	struct iwl_tof_range_rsp_ntfy *resp = (void *)data;

	if (resp->request_id != mvm->tof_data.active_range_request) {
		IWL_ERR(mvm, "Request id mismatch, got %d, active %d\n",
			resp->request_id, mvm->tof_data.active_range_request);
		return -EIO;
	}

	memcpy(&mvm->tof_data.range_resp, resp,
	       sizeof(struct iwl_tof_range_rsp_ntfy));
	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;

	return 0;
}