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
struct sis_sync_cmd_params {int /*<<< orphan*/ * mailbox; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  config_table_length; int /*<<< orphan*/  config_table_offset; int /*<<< orphan*/  max_outstanding_requests; int /*<<< orphan*/  max_transfer_size; int /*<<< orphan*/  max_sg_entries; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_CMD_GET_PQI_CAPABILITIES ; 
 int /*<<< orphan*/  memset (struct sis_sync_cmd_params*,int /*<<< orphan*/ ,int) ; 
 int sis_send_sync_cmd (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct sis_sync_cmd_params*) ; 

int sis_get_pqi_capabilities(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct sis_sync_cmd_params params;

	memset(&params, 0, sizeof(params));

	rc = sis_send_sync_cmd(ctrl_info, SIS_CMD_GET_PQI_CAPABILITIES,
		&params);
	if (rc)
		return rc;

	ctrl_info->max_sg_entries = params.mailbox[1];
	ctrl_info->max_transfer_size = params.mailbox[2];
	ctrl_info->max_outstanding_requests = params.mailbox[3];
	ctrl_info->config_table_offset = params.mailbox[4];
	ctrl_info->config_table_length = params.mailbox[5];

	return 0;
}