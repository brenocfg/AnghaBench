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
typedef  int u32 ;
struct set_ctrl_cfg_req {int* cfg_pg; int /*<<< orphan*/  tag; } ;
struct pm8001_hba_info {int /*<<< orphan*/  pdev; struct inbound_queue_table* inbnd_q_tbl; } ;
struct inbound_queue_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SPCV_12G (int /*<<< orphan*/ ) ; 
 int LTEMPHIL ; 
 int OPC_INB_SET_CONTROLLER_CONFIG ; 
 int RTEMPHIL ; 
 int THERMAL_ENABLE ; 
 int THERMAL_LOG_ENABLE ; 
 int THERMAL_PAGE_CODE_7H ; 
 int THERMAL_PAGE_CODE_8H ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct set_ctrl_cfg_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct set_ctrl_cfg_req*,int /*<<< orphan*/ ) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,int*) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,int) ; 

int
pm80xx_set_thermal_config(struct pm8001_hba_info *pm8001_ha)
{
	struct set_ctrl_cfg_req payload;
	struct inbound_queue_table *circularQ;
	int rc;
	u32 tag;
	u32 opc = OPC_INB_SET_CONTROLLER_CONFIG;
	u32 page_code;

	memset(&payload, 0, sizeof(struct set_ctrl_cfg_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		return -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);

	if (IS_SPCV_12G(pm8001_ha->pdev))
		page_code = THERMAL_PAGE_CODE_7H;
	else
		page_code = THERMAL_PAGE_CODE_8H;

	payload.cfg_pg[0] = (THERMAL_LOG_ENABLE << 9) |
				(THERMAL_ENABLE << 8) | page_code;
	payload.cfg_pg[1] = (LTEMPHIL << 24) | (RTEMPHIL << 8);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	if (rc)
		pm8001_tag_free(pm8001_ha, tag);
	return rc;

}