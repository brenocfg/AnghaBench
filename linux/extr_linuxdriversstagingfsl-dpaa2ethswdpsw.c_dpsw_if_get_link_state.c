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
struct dpsw_rsp_if_get_link_state {int /*<<< orphan*/  up; int /*<<< orphan*/  options; int /*<<< orphan*/  rate; } ;
struct dpsw_link_state {int /*<<< orphan*/  up; int /*<<< orphan*/  options; int /*<<< orphan*/  rate; } ;
struct dpsw_cmd_if_get_link_state {int /*<<< orphan*/  if_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_IF_GET_LINK_STATE ; 
 int /*<<< orphan*/  UP ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpsw_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_if_get_link_state(struct fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   u16 if_id,
			   struct dpsw_link_state *state)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_if_get_link_state *cmd_params;
	struct dpsw_rsp_if_get_link_state *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_GET_LINK_STATE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_if_get_link_state *)cmd.params;
	cmd_params->if_id = cpu_to_le16(if_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpsw_rsp_if_get_link_state *)cmd.params;
	state->rate = le32_to_cpu(rsp_params->rate);
	state->options = le64_to_cpu(rsp_params->options);
	state->up = dpsw_get_field(rsp_params->up, UP);

	return 0;
}