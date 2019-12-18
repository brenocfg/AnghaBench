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
struct snd_pcm_substream {int dummy; } ;
struct snd_dbri {int dummy; } ;
struct dbri_streaminfo {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 struct dbri_streaminfo* DBRI_STREAM (struct snd_dbri*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  D_USR ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  reset_pipe (struct snd_dbri*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_dbri* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  xmit_descs (struct snd_dbri*) ; 

__attribute__((used)) static int snd_dbri_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_dbri *dbri = snd_pcm_substream_chip(substream);
	struct dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dprintk(D_USR, "start audio, period is %d bytes\n",
			(int)snd_pcm_lib_period_bytes(substream));
		/* Re-submit the TDs. */
		xmit_descs(dbri);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		dprintk(D_USR, "stop audio.\n");
		reset_pipe(dbri, info->pipe);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}