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
typedef  int /*<<< orphan*/  u32 ;
struct set_ctrl_cfg_req {int pageCode; int MST_MSI; int STP_SSP_MCT_TMO; int STP_FRM_TMO; int STP_IDLE_TMO; int OPNRJT_RTRY_INTVL; int Data_Cmd_OPNRJT_RTRY_TMO; int Data_Cmd_OPNRJT_RTRY_THR; int MAX_AIP; int /*<<< orphan*/  cfg_pg; int /*<<< orphan*/  tag; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; } ;
struct inbound_queue_table {int dummy; } ;
typedef  struct set_ctrl_cfg_req SASProtocolTimerConfig_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPC_INB_SET_CONTROLLER_CONFIG ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int SAS_COPNRJT_RTRY_THR ; 
 int SAS_COPNRJT_RTRY_TMO ; 
 int SAS_DOPNRJT_RTRY_THR ; 
 int SAS_DOPNRJT_RTRY_TMO ; 
 int SAS_MAX_AIP ; 
 int SAS_MAX_OPEN_TIME ; 
 int SAS_MFD ; 
 int SAS_OPNRJT_RTRY_INTVL ; 
 int SAS_PROTOCOL_TIMER_CONFIG_PAGE ; 
 int SMP_MAX_CONN_TIMER ; 
 int SSP_MCT_TMO ; 
 int STP_FRM_TIMER ; 
 int STP_IDLE_TIME ; 
 int STP_MCT_TMO ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct set_ctrl_cfg_req*,int) ; 
 int /*<<< orphan*/  memset (struct set_ctrl_cfg_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int /*<<< orphan*/ ,struct set_ctrl_cfg_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pm80xx_set_sas_protocol_timer_config(struct pm8001_hba_info *pm8001_ha)
{
	struct set_ctrl_cfg_req payload;
	struct inbound_queue_table *circularQ;
	SASProtocolTimerConfig_t SASConfigPage;
	int rc;
	u32 tag;
	u32 opc = OPC_INB_SET_CONTROLLER_CONFIG;

	memset(&payload, 0, sizeof(struct set_ctrl_cfg_req));
	memset(&SASConfigPage, 0, sizeof(SASProtocolTimerConfig_t));

	rc = pm8001_tag_alloc(pm8001_ha, &tag);

	if (rc)
		return -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);

	SASConfigPage.pageCode        =  SAS_PROTOCOL_TIMER_CONFIG_PAGE;
	SASConfigPage.MST_MSI         =  3 << 15;
	SASConfigPage.STP_SSP_MCT_TMO =  (STP_MCT_TMO << 16) | SSP_MCT_TMO;
	SASConfigPage.STP_FRM_TMO     = (SAS_MAX_OPEN_TIME << 24) |
				(SMP_MAX_CONN_TIMER << 16) | STP_FRM_TIMER;
	SASConfigPage.STP_IDLE_TMO    =  STP_IDLE_TIME;

	if (SASConfigPage.STP_IDLE_TMO > 0x3FFFFFF)
		SASConfigPage.STP_IDLE_TMO = 0x3FFFFFF;


	SASConfigPage.OPNRJT_RTRY_INTVL =         (SAS_MFD << 16) |
						SAS_OPNRJT_RTRY_INTVL;
	SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO =  (SAS_DOPNRJT_RTRY_TMO << 16)
						| SAS_COPNRJT_RTRY_TMO;
	SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR =  (SAS_DOPNRJT_RTRY_THR << 16)
						| SAS_COPNRJT_RTRY_THR;
	SASConfigPage.MAX_AIP =  SAS_MAX_AIP;

	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.pageCode "
			"0x%08x\n", SASConfigPage.pageCode));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.MST_MSI "
			" 0x%08x\n", SASConfigPage.MST_MSI));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.STP_SSP_MCT_TMO "
			" 0x%08x\n", SASConfigPage.STP_SSP_MCT_TMO));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.STP_FRM_TMO "
			" 0x%08x\n", SASConfigPage.STP_FRM_TMO));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.STP_IDLE_TMO "
			" 0x%08x\n", SASConfigPage.STP_IDLE_TMO));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.OPNRJT_RTRY_INTVL "
			" 0x%08x\n", SASConfigPage.OPNRJT_RTRY_INTVL));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO "
			" 0x%08x\n", SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO));
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR "
			" 0x%08x\n", SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR));
	PM8001_INIT_DBG(pm8001_ha, pm8001_printk("SASConfigPage.MAX_AIP "
			" 0x%08x\n", SASConfigPage.MAX_AIP));

	memcpy(&payload.cfg_pg, &SASConfigPage,
			 sizeof(SASProtocolTimerConfig_t));

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	if (rc)
		pm8001_tag_free(pm8001_ha, tag);

	return rc;
}