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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_flow_id; int /*<<< orphan*/  miss_action; } ;
struct dpni_rx_tc_dist_cfg {int /*<<< orphan*/  key_cfg_iova; TYPE_1__ fs_cfg; int /*<<< orphan*/  dist_mode; int /*<<< orphan*/  dist_size; } ;
struct dpni_cmd_set_rx_tc_dist {int /*<<< orphan*/  key_cfg_iova; void* default_flow_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  tc_id; void* dist_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIST_MODE ; 
 int /*<<< orphan*/  DPNI_CMDID_SET_RX_TC_DIST ; 
 int /*<<< orphan*/  MISS_ACTION ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpni_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_set_rx_tc_dist(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 tc_id,
			const struct dpni_rx_tc_dist_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_set_rx_tc_dist *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_SET_RX_TC_DIST,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_set_rx_tc_dist *)cmd.params;
	cmd_params->dist_size = cpu_to_le16(cfg->dist_size);
	cmd_params->tc_id = tc_id;
	dpni_set_field(cmd_params->flags, DIST_MODE, cfg->dist_mode);
	dpni_set_field(cmd_params->flags, MISS_ACTION, cfg->fs_cfg.miss_action);
	cmd_params->default_flow_id = cpu_to_le16(cfg->fs_cfg.default_flow_id);
	cmd_params->key_cfg_iova = cpu_to_le64(cfg->key_cfg_iova);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}