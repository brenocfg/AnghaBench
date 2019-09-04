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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dprtc_time {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_GET_TIME ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_get_time(struct fsl_mc_io *mc_io,
		   u32 cmd_flags,
		   u16 token,
		   uint64_t *time)
{
	struct dprtc_time *rsp_params;
	struct fsl_mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_GET_TIME,
					  cmd_flags,
					  token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dprtc_time *)cmd.params;
	*time = le64_to_cpu(rsp_params->time);

	return 0;
}