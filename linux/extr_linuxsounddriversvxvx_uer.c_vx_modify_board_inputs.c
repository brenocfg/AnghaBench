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
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESYNC_AUDIO_INPUTS ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_modify_board_inputs(struct vx_core *chip)
{
	struct vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_RESYNC_AUDIO_INPUTS);
        rmh.Cmd[0] |= 1 << 0; /* reference: AUDIO 0 */
	return vx_send_msg(chip, &rmh);
}