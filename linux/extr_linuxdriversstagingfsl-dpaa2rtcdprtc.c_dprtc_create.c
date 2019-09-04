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
struct fsl_mc_command {int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dprtc_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_CREATE ; 
 int /*<<< orphan*/  mc_cmd_read_object_id (struct fsl_mc_command*) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_create(struct fsl_mc_io *mc_io,
		 u16 dprc_token,
		 u32 cmd_flags,
		 const struct dprtc_cfg *cfg,
		 u32 *obj_id)
{
	struct fsl_mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_CREATE,
					  cmd_flags,
					  dprc_token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	*obj_id = mc_cmd_read_object_id(&cmd);

	return 0;
}