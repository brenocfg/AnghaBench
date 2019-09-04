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
typedef  scalar_t__ uint64_t ;
struct lpfc_vport {int /*<<< orphan*/  listentry; int /*<<< orphan*/  delayed_disc_tmo; int /*<<< orphan*/  els_tmofunc; int /*<<< orphan*/  fc_disctmo; int /*<<< orphan*/  work_port_lock; int /*<<< orphan*/  rcv_buffer_list; int /*<<< orphan*/  fc_nodes; int /*<<< orphan*/  port_type; int /*<<< orphan*/  cfg_max_luns; scalar_t__ fc_rscn_flush; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  load_flag; struct lpfc_hba* phba; } ;
struct TYPE_4__ {scalar_t__ sge_supp_len; } ;
struct TYPE_5__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {scalar_t__ sli_rev; int cfg_enable_fc4_type; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  port_list; TYPE_3__* pcidev; scalar_t__ cfg_hba_queue_depth; int /*<<< orphan*/  cfg_sg_seg_cnt; TYPE_2__ sli4_hba; int /*<<< orphan*/  cfg_fcp_io_channel; } ;
struct device {int dummy; } ;
struct Scsi_Host {int unique_id; int this_id; int max_cmd_len; int /*<<< orphan*/  transportt; scalar_t__ can_queue; int /*<<< orphan*/  sg_tablesize; scalar_t__ dma_boundary; int /*<<< orphan*/  nr_hw_queues; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_id; scalar_t__ hostdata; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LOADING ; 
 int /*<<< orphan*/  FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_ENABLE_FCP ; 
 int LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  LPFC_MAX_TARGET ; 
 int /*<<< orphan*/  LPFC_NPIV_PORT ; 
 int /*<<< orphan*/  LPFC_PHYSICAL_PORT ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_delayed_disc_tmo ; 
 int /*<<< orphan*/  lpfc_disc_timeout ; 
 int /*<<< orphan*/  lpfc_els_timeout ; 
 int /*<<< orphan*/  lpfc_get_vport_cfgparam (struct lpfc_vport*) ; 
 scalar_t__ lpfc_get_wwpn (struct lpfc_hba*) ; 
 scalar_t__* lpfc_no_hba_reset ; 
 int lpfc_no_hba_reset_cnt ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int lpfc_sli_chipset_init (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_template ; 
 int /*<<< orphan*/  lpfc_template_no_hr ; 
 int /*<<< orphan*/  lpfc_template_nvme ; 
 int /*<<< orphan*/  lpfc_transport_template ; 
 int /*<<< orphan*/  lpfc_vport_template ; 
 int /*<<< orphan*/  lpfc_vport_transport_template ; 
 int scsi_add_host_with_dma (struct Scsi_Host*,struct device*,struct device*) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct lpfc_vport *
lpfc_create_port(struct lpfc_hba *phba, int instance, struct device *dev)
{
	struct lpfc_vport *vport;
	struct Scsi_Host  *shost = NULL;
	int error = 0;
	int i;
	uint64_t wwn;
	bool use_no_reset_hba = false;
	int rc;

	if (lpfc_no_hba_reset_cnt) {
		if (phba->sli_rev < LPFC_SLI_REV4 &&
		    dev == &phba->pcidev->dev) {
			/* Reset the port first */
			lpfc_sli_brdrestart(phba);
			rc = lpfc_sli_chipset_init(phba);
			if (rc)
				return NULL;
		}
		wwn = lpfc_get_wwpn(phba);
	}

	for (i = 0; i < lpfc_no_hba_reset_cnt; i++) {
		if (wwn == lpfc_no_hba_reset[i]) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"6020 Setting use_no_reset port=%llx\n",
					wwn);
			use_no_reset_hba = true;
			break;
		}
	}

	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP) {
		if (dev != &phba->pcidev->dev) {
			shost = scsi_host_alloc(&lpfc_vport_template,
						sizeof(struct lpfc_vport));
		} else {
			if (!use_no_reset_hba)
				shost = scsi_host_alloc(&lpfc_template,
						sizeof(struct lpfc_vport));
			else
				shost = scsi_host_alloc(&lpfc_template_no_hr,
						sizeof(struct lpfc_vport));
		}
	} else if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
		shost = scsi_host_alloc(&lpfc_template_nvme,
					sizeof(struct lpfc_vport));
	}
	if (!shost)
		goto out;

	vport = (struct lpfc_vport *) shost->hostdata;
	vport->phba = phba;
	vport->load_flag |= FC_LOADING;
	vport->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
	vport->fc_rscn_flush = 0;
	lpfc_get_vport_cfgparam(vport);

	shost->unique_id = instance;
	shost->max_id = LPFC_MAX_TARGET;
	shost->max_lun = vport->cfg_max_luns;
	shost->this_id = -1;
	shost->max_cmd_len = 16;
	shost->nr_hw_queues = phba->cfg_fcp_io_channel;
	if (phba->sli_rev == LPFC_SLI_REV4) {
		shost->dma_boundary =
			phba->sli4_hba.pc_sli4_params.sge_supp_len-1;
		shost->sg_tablesize = phba->cfg_sg_seg_cnt;
	}

	/*
	 * Set initial can_queue value since 0 is no longer supported and
	 * scsi_add_host will fail. This will be adjusted later based on the
	 * max xri value determined in hba setup.
	 */
	shost->can_queue = phba->cfg_hba_queue_depth - 10;
	if (dev != &phba->pcidev->dev) {
		shost->transportt = lpfc_vport_transport_template;
		vport->port_type = LPFC_NPIV_PORT;
	} else {
		shost->transportt = lpfc_transport_template;
		vport->port_type = LPFC_PHYSICAL_PORT;
	}

	/* Initialize all internally managed lists. */
	INIT_LIST_HEAD(&vport->fc_nodes);
	INIT_LIST_HEAD(&vport->rcv_buffer_list);
	spin_lock_init(&vport->work_port_lock);

	timer_setup(&vport->fc_disctmo, lpfc_disc_timeout, 0);

	timer_setup(&vport->els_tmofunc, lpfc_els_timeout, 0);

	timer_setup(&vport->delayed_disc_tmo, lpfc_delayed_disc_tmo, 0);

	error = scsi_add_host_with_dma(shost, dev, &phba->pcidev->dev);
	if (error)
		goto out_put_shost;

	spin_lock_irq(&phba->hbalock);
	list_add_tail(&vport->listentry, &phba->port_list);
	spin_unlock_irq(&phba->hbalock);
	return vport;

out_put_shost:
	scsi_host_put(shost);
out:
	return NULL;
}