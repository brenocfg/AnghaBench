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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct scsi_cmnd {int /*<<< orphan*/  request; TYPE_1__* device; } ;
struct lpfc_vector_map_info {int channel_id; } ;
struct lpfc_scsi_buf {struct scsi_cmnd* pCmd; } ;
struct TYPE_4__ {int num_present_cpu; struct lpfc_vector_map_info* cpu_map; } ;
struct lpfc_hba {scalar_t__ cfg_fcp_io_sched; int cfg_fcp_io_channel; int /*<<< orphan*/  fcp_qidx; TYPE_2__ sli4_hba; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ LPFC_FCP_SCHED_BY_CPU ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unique_tag (int /*<<< orphan*/ ) ; 
 int blk_mq_unique_tag_to_hwq (int /*<<< orphan*/ ) ; 
 scalar_t__ shost_use_blk_mq (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

int lpfc_sli4_scmd_to_wqidx_distr(struct lpfc_hba *phba,
				  struct lpfc_scsi_buf *lpfc_cmd)
{
	struct scsi_cmnd *cmnd = lpfc_cmd->pCmd;
	struct lpfc_vector_map_info *cpup;
	int chann, cpu;
	uint32_t tag;
	uint16_t hwq;

	if (cmnd && shost_use_blk_mq(cmnd->device->host)) {
		tag = blk_mq_unique_tag(cmnd->request);
		hwq = blk_mq_unique_tag_to_hwq(tag);

		return hwq;
	}

	if (phba->cfg_fcp_io_sched == LPFC_FCP_SCHED_BY_CPU
	    && phba->cfg_fcp_io_channel > 1) {
		cpu = smp_processor_id();
		if (cpu < phba->sli4_hba.num_present_cpu) {
			cpup = phba->sli4_hba.cpu_map;
			cpup += cpu;
			return cpup->channel_id;
		}
	}
	chann = atomic_add_return(1, &phba->fcp_qidx);
	chann = chann % phba->cfg_fcp_io_channel;
	return chann;
}