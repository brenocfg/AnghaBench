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
struct pcxhr_rmh {int dummy; } ;
struct pcxhr_mgr {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONF_PIPE ; 
 int /*<<< orphan*/  CMD_SEND_IRQA ; 
 int PCXHR_PIPE_STATE_CAPTURE_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  pcxhr_set_pipe_cmd_params (struct pcxhr_rmh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcxhr_toggle_pipes(struct pcxhr_mgr *mgr, int audio_mask)
{
	struct pcxhr_rmh rmh;
	int err;
	int audio = 0;

	while (audio_mask) {
		if (audio_mask & 1) {
			pcxhr_init_rmh(&rmh, CMD_CONF_PIPE);
			if (audio < PCXHR_PIPE_STATE_CAPTURE_OFFSET)
				pcxhr_set_pipe_cmd_params(&rmh, 0, 0, 0,
							  1 << audio);
			else
				pcxhr_set_pipe_cmd_params(&rmh, 1, 0, 0,
							  1 << (audio - PCXHR_PIPE_STATE_CAPTURE_OFFSET));
			err = pcxhr_send_msg(mgr, &rmh);
			if (err) {
				dev_err(&mgr->pci->dev,
					   "error pipe start "
					   "(CMD_CONF_PIPE) err=%x!\n", err);
				return err;
			}
		}
		audio_mask>>=1;
		audio++;
	}
	/* now fire the interrupt on the card */
	pcxhr_init_rmh(&rmh, CMD_SEND_IRQA);
	err = pcxhr_send_msg(mgr, &rmh);
	if (err) {
		dev_err(&mgr->pci->dev,
			   "error pipe start (CMD_SEND_IRQA) err=%x!\n",
			   err);
		return err;
	}
	return 0;
}