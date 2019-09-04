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
struct megasas_instance {int dummy; } ;
struct megasas_cmd_fusion {int cmd_completed; int /*<<< orphan*/  r1_alt_dev_handle; int /*<<< orphan*/  io_request; int /*<<< orphan*/ * scmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void megasas_return_cmd_fusion(struct megasas_instance *instance,
	struct megasas_cmd_fusion *cmd)
{
	cmd->scmd = NULL;
	memset(cmd->io_request, 0, MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE);
	cmd->r1_alt_dev_handle = MR_DEVHANDLE_INVALID;
	cmd->cmd_completed = false;
}