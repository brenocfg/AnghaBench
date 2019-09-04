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
struct dpni_rsp_get_qdid {int /*<<< orphan*/  qdid; } ;
struct dpni_cmd_get_qdid {int qtype; } ;
typedef  enum dpni_queue_type { ____Placeholder_dpni_queue_type } dpni_queue_type ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_GET_QDID ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_get_qdid(struct fsl_mc_io *mc_io,
		  u32 cmd_flags,
		  u16 token,
		  enum dpni_queue_type qtype,
		  u16 *qdid)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_get_qdid *cmd_params;
	struct dpni_rsp_get_qdid *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_QDID,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_get_qdid *)cmd.params;
	cmd_params->qtype = qtype;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpni_rsp_get_qdid *)cmd.params;
	*qdid = le16_to_cpu(rsp_params->qdid);

	return 0;
}