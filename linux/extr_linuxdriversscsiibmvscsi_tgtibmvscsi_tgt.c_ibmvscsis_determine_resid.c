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
struct srp_rsp {void* data_in_res_cnt; int /*<<< orphan*/  flags; void* data_out_res_cnt; } ;
struct se_cmd {int se_cmd_flags; scalar_t__ data_direction; int /*<<< orphan*/  residual_count; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int SCF_OVERFLOW_BIT ; 
 int SCF_UNDERFLOW_BIT ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_DIOVER ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_DIUNDER ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_DOOVER ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_DOUNDER ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvscsis_determine_resid(struct se_cmd *se_cmd,
				      struct srp_rsp *rsp)
{
	u32 residual_count = se_cmd->residual_count;

	if (!residual_count)
		return;

	if (se_cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) {
		if (se_cmd->data_direction == DMA_TO_DEVICE) {
			/* residual data from an underflow write */
			rsp->flags = SRP_RSP_FLAG_DOUNDER;
			rsp->data_out_res_cnt = cpu_to_be32(residual_count);
		} else if (se_cmd->data_direction == DMA_FROM_DEVICE) {
			/* residual data from an underflow read */
			rsp->flags = SRP_RSP_FLAG_DIUNDER;
			rsp->data_in_res_cnt = cpu_to_be32(residual_count);
		}
	} else if (se_cmd->se_cmd_flags & SCF_OVERFLOW_BIT) {
		if (se_cmd->data_direction == DMA_TO_DEVICE) {
			/* residual data from an overflow write */
			rsp->flags = SRP_RSP_FLAG_DOOVER;
			rsp->data_out_res_cnt = cpu_to_be32(residual_count);
		} else if (se_cmd->data_direction == DMA_FROM_DEVICE) {
			/* residual data from an overflow read */
			rsp->flags = SRP_RSP_FLAG_DIOVER;
			rsp->data_in_res_cnt = cpu_to_be32(residual_count);
		}
	}
}