#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  stash_control; } ;
struct TYPE_3__ {int /*<<< orphan*/  hold_active; int /*<<< orphan*/  type; int /*<<< orphan*/  priority; int /*<<< orphan*/  id; } ;
struct dpni_queue {int /*<<< orphan*/  user_context; TYPE_2__ flc; TYPE_1__ destination; } ;
struct dpni_cmd_set_queue {int qtype; void* user_context; void* flc; int /*<<< orphan*/  flags; int /*<<< orphan*/  dest_prio; int /*<<< orphan*/  dest_id; void* options; void* index; void* tc; } ;
typedef  enum dpni_queue_type { ____Placeholder_dpni_queue_type } dpni_queue_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_TYPE ; 
 int /*<<< orphan*/  DPNI_CMDID_SET_QUEUE ; 
 int /*<<< orphan*/  HOLD_ACTIVE ; 
 int /*<<< orphan*/  STASH_CTRL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpni_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_set_queue(struct fsl_mc_io *mc_io,
		   u32 cmd_flags,
		   u16 token,
		   enum dpni_queue_type qtype,
		   u8 tc,
		   u8 index,
		   u8 options,
		   const struct dpni_queue *queue)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_set_queue *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_SET_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_set_queue *)cmd.params;
	cmd_params->qtype = qtype;
	cmd_params->tc = tc;
	cmd_params->index = index;
	cmd_params->options = options;
	cmd_params->dest_id = cpu_to_le32(queue->destination.id);
	cmd_params->dest_prio = queue->destination.priority;
	dpni_set_field(cmd_params->flags, DEST_TYPE, queue->destination.type);
	dpni_set_field(cmd_params->flags, STASH_CTRL, queue->flc.stash_control);
	dpni_set_field(cmd_params->flags, HOLD_ACTIVE,
		       queue->destination.hold_active);
	cmd_params->flc = cpu_to_le64(queue->flc.value);
	cmd_params->user_context = cpu_to_le64(queue->user_context);

	/* send command to mc */
	return mc_send_command(mc_io, &cmd);
}