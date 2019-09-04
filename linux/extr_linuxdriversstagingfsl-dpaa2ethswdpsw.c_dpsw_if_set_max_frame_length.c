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
struct dpsw_cmd_if_set_max_frame_length {void* frame_length; void* if_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_IF_SET_MAX_FRAME_LENGTH ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_if_set_max_frame_length(struct fsl_mc_io *mc_io,
				 u32 cmd_flags,
				 u16 token,
				 u16 if_id,
				 u16 frame_length)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_if_set_max_frame_length *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_IF_SET_MAX_FRAME_LENGTH,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_if_set_max_frame_length *)cmd.params;
	cmd_params->if_id = cpu_to_le16(if_id);
	cmd_params->frame_length = cpu_to_le16(frame_length);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}