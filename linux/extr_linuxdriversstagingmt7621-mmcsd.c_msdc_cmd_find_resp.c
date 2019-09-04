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
typedef  scalar_t__ u32 ;
struct mmc_command {scalar_t__ opcode; scalar_t__ arg; } ;

/* Variables and functions */
 scalar_t__ MMC_CMD_BCR ; 
 scalar_t__ MMC_FAST_IO ; 
 scalar_t__ MMC_GO_IRQ_STATE ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 scalar_t__ MMC_SELECT_CARD ; 
 scalar_t__ MMC_SET_RELATIVE_ADDR ; 
 scalar_t__ RESP_NONE ; 
 scalar_t__ RESP_R1 ; 
 scalar_t__ RESP_R1B ; 
 scalar_t__ RESP_R2 ; 
 scalar_t__ RESP_R3 ; 
 scalar_t__ RESP_R4 ; 
 scalar_t__ RESP_R5 ; 
 scalar_t__ RESP_R6 ; 
 scalar_t__ SD_IO_RW_DIRECT ; 
 scalar_t__ SD_IO_RW_EXTENDED ; 
 scalar_t__ SD_SEND_IF_COND ; 
 scalar_t__ mmc_cmd_type (struct mmc_command*) ; 
 int mmc_resp_type (struct mmc_command*) ; 

__attribute__((used)) static inline u32 msdc_cmd_find_resp(struct mmc_command *cmd)
{
	u32 opcode = cmd->opcode;
	u32 resp;

	if (opcode == MMC_SET_RELATIVE_ADDR) {
		resp = (mmc_cmd_type(cmd) == MMC_CMD_BCR) ? RESP_R6 : RESP_R1;
	} else if (opcode == MMC_FAST_IO) {
		resp = RESP_R4;
	} else if (opcode == MMC_GO_IRQ_STATE) {
		resp = RESP_R5;
	} else if (opcode == MMC_SELECT_CARD) {
		resp = (cmd->arg != 0) ? RESP_R1B : RESP_NONE;
	} else if (opcode == SD_IO_RW_DIRECT || opcode == SD_IO_RW_EXTENDED) {
		resp = RESP_R1; /* SDIO workaround. */
	} else if (opcode == SD_SEND_IF_COND && (mmc_cmd_type(cmd) == MMC_CMD_BCR)) {
		resp = RESP_R1;
	} else {
		switch (mmc_resp_type(cmd)) {
		case MMC_RSP_R1:
			resp = RESP_R1;
			break;
		case MMC_RSP_R1B:
			resp = RESP_R1B;
			break;
		case MMC_RSP_R2:
			resp = RESP_R2;
			break;
		case MMC_RSP_R3:
			resp = RESP_R3;
			break;
		case MMC_RSP_NONE:
		default:
			resp = RESP_NONE;
			break;
		}
	}

	return resp;
}