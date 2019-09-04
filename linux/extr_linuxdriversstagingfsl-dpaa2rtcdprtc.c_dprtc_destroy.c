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
struct dprtc_cmd_destroy {int /*<<< orphan*/  object_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_DESTROY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_destroy(struct fsl_mc_io *mc_io,
		  u16 dprc_token,
		  u32 cmd_flags,
		  u32 object_id)
{
	struct dprtc_cmd_destroy *cmd_params;
	struct fsl_mc_command cmd = { 0 };

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_DESTROY,
					  cmd_flags,
					  dprc_token);
	cmd_params = (struct dprtc_cmd_destroy *)cmd.params;
	cmd_params->object_id = cpu_to_le32(object_id);

	return mc_send_command(mc_io, &cmd);
}