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
struct sof_ipc_pcm_params_reply {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcm_id; } ;
struct snd_sof_pcm {TYPE_1__ pcm; struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int snd_sof_ipc_pcm_params (struct snd_sof_dev*,struct snd_pcm_substream*,struct sof_ipc_pcm_params_reply const*) ; 

__attribute__((used)) static int sof_pcm_dsp_params(struct snd_sof_pcm *spcm, struct snd_pcm_substream *substream,
			      const struct sof_ipc_pcm_params_reply *reply)
{
	struct snd_sof_dev *sdev = spcm->sdev;
	/* validate offset */
	int ret = snd_sof_ipc_pcm_params(sdev, substream, reply);

	if (ret < 0)
		dev_err(sdev->dev, "error: got wrong reply for PCM %d\n",
			spcm->pcm.pcm_id);

	return ret;
}