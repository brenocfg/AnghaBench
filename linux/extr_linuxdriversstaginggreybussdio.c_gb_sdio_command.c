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
typedef  int u8 ;
struct mmc_data {int /*<<< orphan*/  blksz; int /*<<< orphan*/  blocks; } ;
struct mmc_command {int error; void** resp; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct gb_sdio_host {int /*<<< orphan*/  connection; int /*<<< orphan*/  mmc; TYPE_1__* mrq; } ;
struct gb_sdio_command_response {int /*<<< orphan*/ * resp; } ;
struct gb_sdio_command_request {int cmd_flags; int cmd_type; void* data_blksz; void* data_blocks; int /*<<< orphan*/  cmd_arg; int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {struct mmc_data* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int GB_SDIO_CMD_AC ; 
 int GB_SDIO_CMD_ADTC ; 
 int GB_SDIO_CMD_BC ; 
 int GB_SDIO_CMD_BCR ; 
 int GB_SDIO_RSP_NONE ; 
 int GB_SDIO_RSP_R1B ; 
 int GB_SDIO_RSP_R1_R5_R6_R7 ; 
 int GB_SDIO_RSP_R2 ; 
 int GB_SDIO_RSP_R3_R4 ; 
 int /*<<< orphan*/  GB_SDIO_TYPE_COMMAND ; 
#define  MMC_CMD_AC 136 
#define  MMC_CMD_ADTC 135 
#define  MMC_CMD_BC 134 
#define  MMC_CMD_BCR 133 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_sdio_command_request*,int,struct gb_sdio_command_response*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mmc_cmd_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 

__attribute__((used)) static int gb_sdio_command(struct gb_sdio_host *host, struct mmc_command *cmd)
{
	struct gb_sdio_command_request request = {0};
	struct gb_sdio_command_response response;
	struct mmc_data *data = host->mrq->data;
	u8 cmd_flags;
	u8 cmd_type;
	int i;
	int ret;

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		cmd_flags = GB_SDIO_RSP_NONE;
		break;
	case MMC_RSP_R1:
		cmd_flags = GB_SDIO_RSP_R1_R5_R6_R7;
		break;
	case MMC_RSP_R1B:
		cmd_flags = GB_SDIO_RSP_R1B;
		break;
	case MMC_RSP_R2:
		cmd_flags = GB_SDIO_RSP_R2;
		break;
	case MMC_RSP_R3:
		cmd_flags = GB_SDIO_RSP_R3_R4;
		break;
	default:
		dev_err(mmc_dev(host->mmc), "cmd flag invalid 0x%04x\n",
			mmc_resp_type(cmd));
		ret = -EINVAL;
		goto out;
	}

	switch (mmc_cmd_type(cmd)) {
	case MMC_CMD_BC:
		cmd_type = GB_SDIO_CMD_BC;
		break;
	case MMC_CMD_BCR:
		cmd_type = GB_SDIO_CMD_BCR;
		break;
	case MMC_CMD_AC:
		cmd_type = GB_SDIO_CMD_AC;
		break;
	case MMC_CMD_ADTC:
		cmd_type = GB_SDIO_CMD_ADTC;
		break;
	default:
		dev_err(mmc_dev(host->mmc), "cmd type invalid 0x%04x\n",
			mmc_cmd_type(cmd));
		ret = -EINVAL;
		goto out;
	}

	request.cmd = cmd->opcode;
	request.cmd_flags = cmd_flags;
	request.cmd_type = cmd_type;
	request.cmd_arg = cpu_to_le32(cmd->arg);
	/* some controllers need to know at command time data details */
	if (data) {
		request.data_blocks = cpu_to_le16(data->blocks);
		request.data_blksz = cpu_to_le16(data->blksz);
	}

	ret = gb_operation_sync(host->connection, GB_SDIO_TYPE_COMMAND,
				&request, sizeof(request), &response,
				sizeof(response));
	if (ret < 0)
		goto out;

	/* no response expected */
	if (cmd_flags == GB_SDIO_RSP_NONE)
		goto out;

	/* long response expected */
	if (cmd_flags & GB_SDIO_RSP_R2)
		for (i = 0; i < 4; i++)
			cmd->resp[i] = le32_to_cpu(response.resp[i]);
	else
		cmd->resp[0] = le32_to_cpu(response.resp[0]);

out:
	cmd->error = ret;
	return ret;
}