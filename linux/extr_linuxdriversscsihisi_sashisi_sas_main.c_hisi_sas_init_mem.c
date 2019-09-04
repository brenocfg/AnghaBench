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
struct hisi_sas_sata_breakpoint {int dummy; } ;
struct hisi_sas_iost {int dummy; } ;
struct hisi_sas_initial_fis {int dummy; } ;
struct hisi_sas_dq {scalar_t__ wr_point; } ;
struct hisi_sas_cq {scalar_t__ rd_point; } ;
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_sas_breakpoint {int dummy; } ;
struct hisi_hba {int queue_count; int n_phy; int /*<<< orphan*/  sata_breakpoint; int /*<<< orphan*/  breakpoint; int /*<<< orphan*/  iost; int /*<<< orphan*/  initial_fis; int /*<<< orphan*/ * complete_hdr; TYPE_1__* hw; int /*<<< orphan*/ * cmd_hdr; struct hisi_sas_dq* dq; struct hisi_sas_cq* cq; } ;
struct TYPE_2__ {int max_command_entries; int complete_hdr_size; } ;

/* Variables and functions */
 int HISI_SAS_MAX_ITCT_ENTRIES ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hisi_sas_init_mem(struct hisi_hba *hisi_hba)
{
	int i, s, max_command_entries = hisi_hba->hw->max_command_entries;

	for (i = 0; i < hisi_hba->queue_count; i++) {
		struct hisi_sas_cq *cq = &hisi_hba->cq[i];
		struct hisi_sas_dq *dq = &hisi_hba->dq[i];

		s = sizeof(struct hisi_sas_cmd_hdr) * HISI_SAS_QUEUE_SLOTS;
		memset(hisi_hba->cmd_hdr[i], 0, s);
		dq->wr_point = 0;

		s = hisi_hba->hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
		memset(hisi_hba->complete_hdr[i], 0, s);
		cq->rd_point = 0;
	}

	s = sizeof(struct hisi_sas_initial_fis) * hisi_hba->n_phy;
	memset(hisi_hba->initial_fis, 0, s);

	s = max_command_entries * sizeof(struct hisi_sas_iost);
	memset(hisi_hba->iost, 0, s);

	s = max_command_entries * sizeof(struct hisi_sas_breakpoint);
	memset(hisi_hba->breakpoint, 0, s);

	s = HISI_SAS_MAX_ITCT_ENTRIES * sizeof(struct hisi_sas_sata_breakpoint);
	memset(hisi_hba->sata_breakpoint, 0, s);
}