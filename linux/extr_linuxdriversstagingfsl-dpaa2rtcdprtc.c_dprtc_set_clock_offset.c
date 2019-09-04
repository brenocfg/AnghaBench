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
struct dprtc_cmd_set_clock_offset {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_SET_CLOCK_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_set_clock_offset(struct fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   int64_t offset)
{
	struct dprtc_cmd_set_clock_offset *cmd_params;
	struct fsl_mc_command cmd = { 0 };

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_SET_CLOCK_OFFSET,
					  cmd_flags,
					  token);
	cmd_params = (struct dprtc_cmd_set_clock_offset *)cmd.params;
	cmd_params->offset = cpu_to_le64(offset);

	return mc_send_command(mc_io, &cmd);
}