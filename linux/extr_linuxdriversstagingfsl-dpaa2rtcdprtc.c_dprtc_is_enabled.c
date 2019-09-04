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
struct dprtc_rsp_is_enabled {int /*<<< orphan*/  en; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_IS_ENABLED ; 
 int /*<<< orphan*/  ENABLE ; 
 int dprtc_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_is_enabled(struct fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     int *en)
{
	struct dprtc_rsp_is_enabled *rsp_params;
	struct fsl_mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_IS_ENABLED, cmd_flags,
					  token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dprtc_rsp_is_enabled *)cmd.params;
	*en = dprtc_get_field(rsp_params->en, ENABLE);

	return 0;
}