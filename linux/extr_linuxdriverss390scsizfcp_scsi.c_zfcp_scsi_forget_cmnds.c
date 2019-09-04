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
typedef  scalar_t__ u8 ;
struct zfcp_scsi_req_filter {int /*<<< orphan*/  lun_handle; scalar_t__ tmf_scope; int /*<<< orphan*/  port_handle; } ;
struct zfcp_scsi_dev {int /*<<< orphan*/  lun_handle; TYPE_1__* port; } ;
struct zfcp_adapter {int /*<<< orphan*/  abort_lock; int /*<<< orphan*/  req_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; struct zfcp_adapter* adapter; } ;

/* Variables and functions */
 scalar_t__ FCP_TMF_LUN_RESET ; 
 scalar_t__ FCP_TMF_TGT_RESET ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_reqlist_apply_for_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zfcp_scsi_req_filter*) ; 
 int /*<<< orphan*/  zfcp_scsi_forget_cmnd ; 

__attribute__((used)) static void zfcp_scsi_forget_cmnds(struct zfcp_scsi_dev *zsdev, u8 tm_flags)
{
	struct zfcp_adapter *adapter = zsdev->port->adapter;
	struct zfcp_scsi_req_filter filter = {
		.tmf_scope = FCP_TMF_TGT_RESET,
		.port_handle = zsdev->port->handle,
	};
	unsigned long flags;

	if (tm_flags == FCP_TMF_LUN_RESET) {
		filter.tmf_scope = FCP_TMF_LUN_RESET;
		filter.lun_handle = zsdev->lun_handle;
	}

	/*
	 * abort_lock secures against other processings - in the abort-function
	 * and normal cmnd-handler - of (struct zfcp_fsf_req *)->data
	 */
	write_lock_irqsave(&adapter->abort_lock, flags);
	zfcp_reqlist_apply_for_all(adapter->req_list, zfcp_scsi_forget_cmnd,
				   &filter);
	write_unlock_irqrestore(&adapter->abort_lock, flags);
}