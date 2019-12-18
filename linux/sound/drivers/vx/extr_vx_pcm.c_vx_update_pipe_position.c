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
typedef  int u64 ;
struct vx_rmh {int* Stat; } ;
struct vx_pipe {int cur_count; int position; int transferred; int /*<<< orphan*/  number; int /*<<< orphan*/  is_capture; } ;
struct vx_core {int dummy; } ;
struct snd_pcm_runtime {int buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STREAM_SAMPLE_COUNT ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 
 int /*<<< orphan*/  vx_set_pipe_cmd_params (struct vx_rmh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_update_pipe_position(struct vx_core *chip,
				   struct snd_pcm_runtime *runtime,
				   struct vx_pipe *pipe)
{
	struct vx_rmh rmh;
	int err, update;
	u64 count;

	vx_init_rmh(&rmh, CMD_STREAM_SAMPLE_COUNT);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	err = vx_send_msg(chip, &rmh);
	if (err < 0)
		return err;

	count = ((u64)(rmh.Stat[0] & 0xfffff) << 24) | (u64)rmh.Stat[1];
	update = (int)(count - pipe->cur_count);
	pipe->cur_count = count;
	pipe->position += update;
	if (pipe->position >= (int)runtime->buffer_size)
		pipe->position %= runtime->buffer_size;
	pipe->transferred += update;
	return 0;
}