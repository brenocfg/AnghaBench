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
struct vx_rmh {int /*<<< orphan*/ * Cmd; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MODIFY_CLOCK ; 
 int /*<<< orphan*/  CMD_MODIFY_CLOCK_S_BIT ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_modify_board_clock(struct vx_core *chip, int sync)
{
	struct vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_MODIFY_CLOCK);
	/* Ask the DSP to resynchronize its FIFO. */
	if (sync)
		rmh.Cmd[0] |= CMD_MODIFY_CLOCK_S_BIT;
	return vx_send_msg(chip, &rmh);
}