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
struct pci_dev {int dummy; } ;
struct ipr_ioa_cfg {int max_devs_supported; int cfg_table_size; TYPE_1__* hrrq; struct Scsi_Host* host; int /*<<< orphan*/  max_cmds; scalar_t__ sis64; int /*<<< orphan*/  sdt_state; int /*<<< orphan*/  eeh_wait_q; int /*<<< orphan*/  msi_wait_q; int /*<<< orphan*/  reset_wait_q; int /*<<< orphan*/  scsi_add_work_q; int /*<<< orphan*/  work_q; int /*<<< orphan*/  used_res_q; int /*<<< orphan*/  free_res_q; int /*<<< orphan*/  hostrcb_report_q; int /*<<< orphan*/  hostrcb_pending_q; int /*<<< orphan*/  hostrcb_free_q; int /*<<< orphan*/  ipr_cmd_label; int /*<<< orphan*/  ipr_hcam_label; int /*<<< orphan*/  resource_table_label; int /*<<< orphan*/  cfg_table_start; int /*<<< orphan*/  trace_start; int /*<<< orphan*/  eye_catcher; int /*<<< orphan*/  doorbell; int /*<<< orphan*/  log_level; struct pci_dev* pdev; } ;
struct ipr_config_table_hdr64 {int dummy; } ;
struct ipr_config_table_hdr {int dummy; } ;
struct ipr_config_table_entry64 {int dummy; } ;
struct ipr_config_table_entry {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; int /*<<< orphan*/  can_queue; int /*<<< orphan*/  max_cmd_len; int /*<<< orphan*/  host_no; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  max_channel; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  _lock; int /*<<< orphan*/ * lock; int /*<<< orphan*/  hrrq_pending_q; int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  INACTIVE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* IPR_CFG_TBL_START ; 
 char* IPR_CMD_LABEL ; 
 int /*<<< orphan*/  IPR_DOORBELL ; 
 char* IPR_EYECATCHER ; 
 char* IPR_HCAM_LABEL ; 
 int /*<<< orphan*/  IPR_MAX_CDB_LEN ; 
 int /*<<< orphan*/  IPR_MAX_NUM_LUNS_PER_TARGET ; 
 int /*<<< orphan*/  IPR_MAX_NUM_TARGETS_PER_BUS ; 
 scalar_t__ IPR_MAX_PHYSICAL_DEVS ; 
 scalar_t__ IPR_MAX_SIS64_DEVS ; 
 int /*<<< orphan*/  IPR_MAX_SIS64_LUNS_PER_TARGET ; 
 int /*<<< orphan*/  IPR_MAX_SIS64_TARGETS_PER_BUS ; 
 char* IPR_RES_TABLE_LABEL ; 
 char* IPR_TRACE_START_LABEL ; 
 int /*<<< orphan*/  IPR_VSET_BUS ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_add_remove_thread ; 
 int /*<<< orphan*/  ipr_initialize_bus_attr (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_log_level ; 
 scalar_t__ ipr_max_devs ; 
 int /*<<< orphan*/  ipr_worker_thread ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ipr_init_ioa_cfg(struct ipr_ioa_cfg *ioa_cfg,
			     struct Scsi_Host *host, struct pci_dev *pdev)
{
	int i;

	ioa_cfg->host = host;
	ioa_cfg->pdev = pdev;
	ioa_cfg->log_level = ipr_log_level;
	ioa_cfg->doorbell = IPR_DOORBELL;
	sprintf(ioa_cfg->eye_catcher, IPR_EYECATCHER);
	sprintf(ioa_cfg->trace_start, IPR_TRACE_START_LABEL);
	sprintf(ioa_cfg->cfg_table_start, IPR_CFG_TBL_START);
	sprintf(ioa_cfg->resource_table_label, IPR_RES_TABLE_LABEL);
	sprintf(ioa_cfg->ipr_hcam_label, IPR_HCAM_LABEL);
	sprintf(ioa_cfg->ipr_cmd_label, IPR_CMD_LABEL);

	INIT_LIST_HEAD(&ioa_cfg->hostrcb_free_q);
	INIT_LIST_HEAD(&ioa_cfg->hostrcb_pending_q);
	INIT_LIST_HEAD(&ioa_cfg->hostrcb_report_q);
	INIT_LIST_HEAD(&ioa_cfg->free_res_q);
	INIT_LIST_HEAD(&ioa_cfg->used_res_q);
	INIT_WORK(&ioa_cfg->work_q, ipr_worker_thread);
	INIT_WORK(&ioa_cfg->scsi_add_work_q, ipr_add_remove_thread);
	init_waitqueue_head(&ioa_cfg->reset_wait_q);
	init_waitqueue_head(&ioa_cfg->msi_wait_q);
	init_waitqueue_head(&ioa_cfg->eeh_wait_q);
	ioa_cfg->sdt_state = INACTIVE;

	ipr_initialize_bus_attr(ioa_cfg);
	ioa_cfg->max_devs_supported = ipr_max_devs;

	if (ioa_cfg->sis64) {
		host->max_id = IPR_MAX_SIS64_TARGETS_PER_BUS;
		host->max_lun = IPR_MAX_SIS64_LUNS_PER_TARGET;
		if (ipr_max_devs > IPR_MAX_SIS64_DEVS)
			ioa_cfg->max_devs_supported = IPR_MAX_SIS64_DEVS;
		ioa_cfg->cfg_table_size = (sizeof(struct ipr_config_table_hdr64)
					   + ((sizeof(struct ipr_config_table_entry64)
					       * ioa_cfg->max_devs_supported)));
	} else {
		host->max_id = IPR_MAX_NUM_TARGETS_PER_BUS;
		host->max_lun = IPR_MAX_NUM_LUNS_PER_TARGET;
		if (ipr_max_devs > IPR_MAX_PHYSICAL_DEVS)
			ioa_cfg->max_devs_supported = IPR_MAX_PHYSICAL_DEVS;
		ioa_cfg->cfg_table_size = (sizeof(struct ipr_config_table_hdr)
					   + ((sizeof(struct ipr_config_table_entry)
					       * ioa_cfg->max_devs_supported)));
	}

	host->max_channel = IPR_VSET_BUS;
	host->unique_id = host->host_no;
	host->max_cmd_len = IPR_MAX_CDB_LEN;
	host->can_queue = ioa_cfg->max_cmds;
	pci_set_drvdata(pdev, ioa_cfg);

	for (i = 0; i < ARRAY_SIZE(ioa_cfg->hrrq); i++) {
		INIT_LIST_HEAD(&ioa_cfg->hrrq[i].hrrq_free_q);
		INIT_LIST_HEAD(&ioa_cfg->hrrq[i].hrrq_pending_q);
		spin_lock_init(&ioa_cfg->hrrq[i]._lock);
		if (i == 0)
			ioa_cfg->hrrq[i].lock = ioa_cfg->host->host_lock;
		else
			ioa_cfg->hrrq[i].lock = &ioa_cfg->hrrq[i]._lock;
	}
}