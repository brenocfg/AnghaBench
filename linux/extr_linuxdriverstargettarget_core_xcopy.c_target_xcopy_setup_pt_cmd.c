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
struct se_cmd {int /*<<< orphan*/  t_data_nents; int /*<<< orphan*/  t_data_sg; int /*<<< orphan*/  se_cmd_flags; int /*<<< orphan*/  data_length; scalar_t__ tag; } ;
struct xcopy_pt_cmd {struct xcopy_op* xcopy_op; struct se_cmd se_cmd; } ;
struct xcopy_op {int /*<<< orphan*/  xop_data_nents; int /*<<< orphan*/  xop_data_sg; } ;
struct se_device {int dummy; } ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int target_alloc_sgl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ target_setup_cmd_from_cdb (struct se_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  target_xcopy_init_pt_lun (struct se_device*,struct se_cmd*,int) ; 
 int /*<<< orphan*/  target_xcopy_setup_pt_port (struct xcopy_pt_cmd*,struct xcopy_op*,int) ; 
 scalar_t__ transport_generic_map_mem_to_cmd (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int target_xcopy_setup_pt_cmd(
	struct xcopy_pt_cmd *xpt_cmd,
	struct xcopy_op *xop,
	struct se_device *se_dev,
	unsigned char *cdb,
	bool remote_port,
	bool alloc_mem)
{
	struct se_cmd *cmd = &xpt_cmd->se_cmd;
	sense_reason_t sense_rc;
	int ret = 0, rc;
	/*
	 * Setup LUN+port to honor reservations based upon xop->op_origin for
	 * X-COPY PUSH or X-COPY PULL based upon where the CDB was received.
	 */
	target_xcopy_init_pt_lun(se_dev, cmd, remote_port);

	xpt_cmd->xcopy_op = xop;
	target_xcopy_setup_pt_port(xpt_cmd, xop, remote_port);

	cmd->tag = 0;
	sense_rc = target_setup_cmd_from_cdb(cmd, cdb);
	if (sense_rc) {
		ret = -EINVAL;
		goto out;
	}

	if (alloc_mem) {
		rc = target_alloc_sgl(&cmd->t_data_sg, &cmd->t_data_nents,
				      cmd->data_length, false, false);
		if (rc < 0) {
			ret = rc;
			goto out;
		}
		/*
		 * Set this bit so that transport_free_pages() allows the
		 * caller to release SGLs + physical memory allocated by
		 * transport_generic_get_mem()..
		 */
		cmd->se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	} else {
		/*
		 * Here the previously allocated SGLs for the internal READ
		 * are mapped zero-copy to the internal WRITE.
		 */
		sense_rc = transport_generic_map_mem_to_cmd(cmd,
					xop->xop_data_sg, xop->xop_data_nents,
					NULL, 0);
		if (sense_rc) {
			ret = -EINVAL;
			goto out;
		}

		pr_debug("Setup PASSTHROUGH_NOALLOC t_data_sg: %p t_data_nents:"
			 " %u\n", cmd->t_data_sg, cmd->t_data_nents);
	}

	return 0;

out:
	return ret;
}