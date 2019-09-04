#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_cmd {scalar_t__ release; int /*<<< orphan*/  wait_for_completion; scalar_t__ completion_req; TYPE_3__* ioa_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_6__ {TYPE_2__ ioasa; TYPE_1__ ioarcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_return_cmd (struct pmcraid_cmd*) ; 

__attribute__((used)) static void pmcraid_internal_done(struct pmcraid_cmd *cmd)
{
	pmcraid_info("response internal cmd CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	/* Some of the internal commands are sent with callers blocking for the
	 * response. Same will be indicated as part of cmd->completion_req
	 * field. Response path needs to wake up any waiters waiting for cmd
	 * completion if this flag is set.
	 */
	if (cmd->completion_req) {
		cmd->completion_req = 0;
		complete(&cmd->wait_for_completion);
	}

	/* most of the internal commands are completed by caller itself, so
	 * no need to return the command block back to free pool until we are
	 * required to do so (e.g once done with initialization).
	 */
	if (cmd->release) {
		cmd->release = 0;
		pmcraid_return_cmd(cmd);
	}
}