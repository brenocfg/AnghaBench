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
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpsw_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; } ;
struct dpsw_cmd_if_set_link_cfg {int /*<<< orphan*/  options; int /*<<< orphan*/  rate; int /*<<< orphan*/  if_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_IF_SET_LINK_CFG ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_if_set_link_cfg(struct fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u16 if_id,
			 struct dpsw_link_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_if_set_link_cfg *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_LINK_CFG,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_if_set_link_cfg *)cmd.params;
	cmd_params->if_id = cpu_to_le16(if_id);
	cmd_params->rate = cpu_to_le32(cfg->rate);
	cmd_params->options = cpu_to_le64(cfg->options);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}