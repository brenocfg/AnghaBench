#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcxhr_rmh {int* cmd; int /*<<< orphan*/  cmd_len; } ;
struct pcxhr_pipe {int is_capture; int first_audio; int /*<<< orphan*/  status; } ;
struct pcxhr_mgr {TYPE_1__* pci; scalar_t__ mono_capture; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RES_PIPE ; 
 scalar_t__ DSP_EXT_CMD_SET (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  PCXHR_PIPE_DEFINED ; 
 int PCXHR_PLAYBACK_STREAMS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_set_pipe_cmd_params (struct pcxhr_rmh*,int,int,int,int) ; 

__attribute__((used)) static int pcxhr_dsp_allocate_pipe(struct pcxhr_mgr *mgr,
				   struct pcxhr_pipe *pipe,
				   int is_capture, int pin)
{
	int stream_count, audio_count;
	int err;
	struct pcxhr_rmh rmh;

	if (is_capture) {
		stream_count = 1;
		if (mgr->mono_capture)
			audio_count = 1;
		else
			audio_count = 2;
	} else {
		stream_count = PCXHR_PLAYBACK_STREAMS;
		audio_count = 2;	/* always stereo */
	}
	dev_dbg(&mgr->pci->dev, "snd_add_ref_pipe pin(%d) pcm%c0\n",
		    pin, is_capture ? 'c' : 'p');
	pipe->is_capture = is_capture;
	pipe->first_audio = pin;
	/* define pipe (P_PCM_ONLY_MASK (0x020000) is not necessary) */
	pcxhr_init_rmh(&rmh, CMD_RES_PIPE);
	pcxhr_set_pipe_cmd_params(&rmh, is_capture, pin,
				  audio_count, stream_count);
	rmh.cmd[1] |= 0x020000; /* add P_PCM_ONLY_MASK */
	if (DSP_EXT_CMD_SET(mgr)) {
		/* add channel mask to command */
	  rmh.cmd[rmh.cmd_len++] = (audio_count == 1) ? 0x01 : 0x03;
	}
	err = pcxhr_send_msg(mgr, &rmh);
	if (err < 0) {
		dev_err(&mgr->pci->dev, "error pipe allocation "
			   "(CMD_RES_PIPE) err=%x!\n", err);
		return err;
	}
	pipe->status = PCXHR_PIPE_DEFINED;

	return 0;
}