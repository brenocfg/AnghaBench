#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * data; scalar_t__ segment_size; scalar_t__ data_size; int /*<<< orphan*/  seq_num; void* process_status; } ;
struct TYPE_13__ {int /*<<< orphan*/  seq_num; void* process_status; } ;
struct TYPE_12__ {int /*<<< orphan*/  seq_num; void* process_status; } ;
struct TYPE_11__ {int /*<<< orphan*/  seq_num; void* process_status; } ;
struct TYPE_10__ {int /*<<< orphan*/  seq_num; void* process_status; int /*<<< orphan*/  scan_cmd_construct_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  seq_num; void* process_status; int /*<<< orphan*/  cfg_para_cmd_construct_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  seq_num; void* process_status; int /*<<< orphan*/  efuse_cmd_construct_state; } ;
struct halmac_state {TYPE_7__ psd_set; TYPE_6__ power_tracking_set; TYPE_5__ iqk_set; TYPE_4__ update_packet_set; TYPE_3__ scan_state_set; TYPE_2__ cfg_para_state_set; TYPE_1__ efuse_state_set; } ;
struct halmac_adapter {int /*<<< orphan*/  h2c_packet_seq; struct halmac_state halmac_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE ; 
 void* HALMAC_CMD_PROCESS_IDLE ; 
 int /*<<< orphan*/  HALMAC_EFUSE_CMD_CONSTRUCT_IDLE ; 
 int /*<<< orphan*/  HALMAC_SCAN_CMD_CONSTRUCT_IDLE ; 

void halmac_init_offload_feature_state_machine_88xx(
	struct halmac_adapter *halmac_adapter)
{
	struct halmac_state *state = &halmac_adapter->halmac_state;

	state->efuse_state_set.efuse_cmd_construct_state =
		HALMAC_EFUSE_CMD_CONSTRUCT_IDLE;
	state->efuse_state_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->efuse_state_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->cfg_para_state_set.cfg_para_cmd_construct_state =
		HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE;
	state->cfg_para_state_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->cfg_para_state_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->scan_state_set.scan_cmd_construct_state =
		HALMAC_SCAN_CMD_CONSTRUCT_IDLE;
	state->scan_state_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->scan_state_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->update_packet_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->update_packet_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->iqk_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->iqk_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->power_tracking_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->power_tracking_set.seq_num = halmac_adapter->h2c_packet_seq;

	state->psd_set.process_status = HALMAC_CMD_PROCESS_IDLE;
	state->psd_set.seq_num = halmac_adapter->h2c_packet_seq;
	state->psd_set.data_size = 0;
	state->psd_set.segment_size = 0;
	state->psd_set.data = NULL;
}