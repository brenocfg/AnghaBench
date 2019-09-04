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
struct beiscsi_hba {int dummy; } ;
struct be_set_eqd {int eq_id; int delay_multiplier; } ;
struct be_dma_mem {struct be_cmd_req_modify_eq_delay* va; } ;
struct be_cmd_req_modify_eq_delay {TYPE_1__* delay; void* num_eq; } ;
struct TYPE_2__ {void* delay_multiplier; scalar_t__ phase; void* eq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_MODIFY_EQ_DELAY ; 
 int /*<<< orphan*/  __beiscsi_eq_delay_compl ; 
 int beiscsi_exec_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int beiscsi_prep_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (int) ; 

int beiscsi_modify_eq_delay(struct beiscsi_hba *phba,
			    struct be_set_eqd *set_eqd, int num)
{
	struct be_cmd_req_modify_eq_delay *req;
	struct be_dma_mem nonemb_cmd;
	int i, rc;

	rc = beiscsi_prep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_MODIFY_EQ_DELAY, sizeof(*req));
	if (rc)
		return rc;

	req = nonemb_cmd.va;
	req->num_eq = cpu_to_le32(num);
	for (i = 0; i < num; i++) {
		req->delay[i].eq_id = cpu_to_le32(set_eqd[i].eq_id);
		req->delay[i].phase = 0;
		req->delay[i].delay_multiplier =
				cpu_to_le32(set_eqd[i].delay_multiplier);
	}

	return beiscsi_exec_nemb_cmd(phba, &nonemb_cmd,
				     __beiscsi_eq_delay_compl, NULL, 0);
}