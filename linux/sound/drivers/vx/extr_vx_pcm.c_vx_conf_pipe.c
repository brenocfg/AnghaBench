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
struct vx_rmh {int* Cmd; } ;
struct vx_pipe {int number; scalar_t__ is_capture; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONF_PIPE ; 
 int COMMAND_RECORD_MASK ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_conf_pipe(struct vx_core *chip, struct vx_pipe *pipe)
{
	struct vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_CONF_PIPE);
	if (pipe->is_capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
	rmh.Cmd[1] = 1 << pipe->number;
	return vx_send_msg(chip, &rmh);
}