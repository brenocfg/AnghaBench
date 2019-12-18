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
struct vx_pipe {int number; int is_capture; int channels; int data_mode; scalar_t__ pcx_time; scalar_t__ differed_type; } ;
struct vx_core {int uer_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_DATA_MODE ; 
 int /*<<< orphan*/  BIT_SKIP_SOUND ; 
 int /*<<< orphan*/  CMD_FREE_PIPE ; 
 int /*<<< orphan*/  CMD_RES_PIPE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEC958_AES0_NONAUDIO ; 
 struct vx_pipe* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ underrun_skip_sound ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg (struct vx_core*,struct vx_rmh*) ; 
 int /*<<< orphan*/  vx_set_pipe_cmd_params (struct vx_rmh*,int,int,int) ; 

__attribute__((used)) static int vx_alloc_pipe(struct vx_core *chip, int capture,
			 int audioid, int num_audio,
			 struct vx_pipe **pipep)
{
	int err;
	struct vx_pipe *pipe;
	struct vx_rmh rmh;
	int data_mode;

	*pipep = NULL;
	vx_init_rmh(&rmh, CMD_RES_PIPE);
	vx_set_pipe_cmd_params(&rmh, capture, audioid, num_audio);
#if 0	// NYI
	if (underrun_skip_sound)
		rmh.Cmd[0] |= BIT_SKIP_SOUND;
#endif	// NYI
	data_mode = (chip->uer_bits & IEC958_AES0_NONAUDIO) != 0;
	if (! capture && data_mode)
		rmh.Cmd[0] |= BIT_DATA_MODE;
	err = vx_send_msg(chip, &rmh);
	if (err < 0)
		return err;

	/* initialize the pipe record */
	pipe = kzalloc(sizeof(*pipe), GFP_KERNEL);
	if (! pipe) {
		/* release the pipe */
		vx_init_rmh(&rmh, CMD_FREE_PIPE);
		vx_set_pipe_cmd_params(&rmh, capture, audioid, 0);
		vx_send_msg(chip, &rmh);
		return -ENOMEM;
	}

	/* the pipe index should be identical with the audio index */
	pipe->number = audioid;
	pipe->is_capture = capture;
	pipe->channels = num_audio;
	pipe->differed_type = 0;
	pipe->pcx_time = 0;
	pipe->data_mode = data_mode;
	*pipep = pipe;

	return 0;
}