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
struct vx_rmh {int dummy; } ;
struct vx_pipe {int /*<<< orphan*/  number; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NOTIFY_END_OF_BUFFER ; 
 int /*<<< orphan*/  IRQ_PAUSE_START_CONNECT ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg_nolock (struct vx_core*,struct vx_rmh*) ; 
 int /*<<< orphan*/  vx_send_rih_nolock (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_set_stream_cmd_params (struct vx_rmh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_notify_end_of_buffer(struct vx_core *chip, struct vx_pipe *pipe)
{
	int err;
	struct vx_rmh rmh;  /* use a temporary rmh here */

	/* Toggle Dsp Host Interface into Message mode */
	vx_send_rih_nolock(chip, IRQ_PAUSE_START_CONNECT);
	vx_init_rmh(&rmh, CMD_NOTIFY_END_OF_BUFFER);
	vx_set_stream_cmd_params(&rmh, 0, pipe->number);
	err = vx_send_msg_nolock(chip, &rmh);
	if (err < 0)
		return err;
	/* Toggle Dsp Host Interface back to sound transfer mode */
	vx_send_rih_nolock(chip, IRQ_PAUSE_START_CONNECT);
	return 0;
}