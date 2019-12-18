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
struct TYPE_2__ {int length; void* command_id; int /*<<< orphan*/  dst; } ;
struct sst_param_sba_ssp_slot_map {int param_len; TYPE_1__ header; int /*<<< orphan*/  tx_slot_map; int /*<<< orphan*/  rx_slot_map; int /*<<< orphan*/  ssp_index; void* param_id; } ;
struct sst_dsp_header {int dummy; } ;
struct sst_data {int dummy; } ;

/* Variables and functions */
 void* SBA_SET_SSP_SLOT_MAP ; 
 int /*<<< orphan*/  SSP_CODEC ; 
 int /*<<< orphan*/  SST_FILL_DEFAULT_DESTINATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SST_FLAG_BLOCKED ; 
 int /*<<< orphan*/  SST_IPC_IA_SET_PARAMS ; 
 int /*<<< orphan*/  SST_TASK_SBA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sst_fill_and_send_cmd_unlocked (struct sst_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sst_param_sba_ssp_slot_map*,int) ; 
 int /*<<< orphan*/ * sst_ssp_rx_map ; 
 int /*<<< orphan*/ * sst_ssp_tx_map ; 

__attribute__((used)) static int sst_send_slot_map(struct sst_data *drv)
{
	struct sst_param_sba_ssp_slot_map cmd;

	SST_FILL_DEFAULT_DESTINATION(cmd.header.dst);
	cmd.header.command_id = SBA_SET_SSP_SLOT_MAP;
	cmd.header.length = sizeof(struct sst_param_sba_ssp_slot_map)
				- sizeof(struct sst_dsp_header);

	cmd.param_id = SBA_SET_SSP_SLOT_MAP;
	cmd.param_len = sizeof(cmd.rx_slot_map) + sizeof(cmd.tx_slot_map)
					+ sizeof(cmd.ssp_index);
	cmd.ssp_index = SSP_CODEC;

	memcpy(cmd.rx_slot_map, &sst_ssp_tx_map[0], sizeof(cmd.rx_slot_map));
	memcpy(cmd.tx_slot_map, &sst_ssp_rx_map[0], sizeof(cmd.tx_slot_map));

	return sst_fill_and_send_cmd_unlocked(drv, SST_IPC_IA_SET_PARAMS,
			SST_FLAG_BLOCKED, SST_TASK_SBA, 0, &cmd,
			      sizeof(cmd.header) + cmd.header.length);
}