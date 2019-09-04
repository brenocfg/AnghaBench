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
struct tcmu_cmd {struct se_cmd* se_cmd; } ;
struct se_cmd {int /*<<< orphan*/  t_task_cdb; } ;

/* Variables and functions */
 int TCMU_OP_ALIGN_SIZE ; 
 int /*<<< orphan*/  WARN_ON (size_t) ; 
 size_t round_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_command_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t tcmu_cmd_get_cmd_size(struct tcmu_cmd *tcmu_cmd,
					   size_t base_command_size)
{
	struct se_cmd *se_cmd = tcmu_cmd->se_cmd;
	size_t command_size;

	command_size = base_command_size +
		round_up(scsi_command_size(se_cmd->t_task_cdb),
				TCMU_OP_ALIGN_SIZE);

	WARN_ON(command_size & (TCMU_OP_ALIGN_SIZE-1));

	return command_size;
}