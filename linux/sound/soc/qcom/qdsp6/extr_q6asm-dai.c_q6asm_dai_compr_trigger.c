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
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct q6asm_dai_rtd* private_data; } ;
struct q6asm_dai_rtd {int /*<<< orphan*/  audio_client; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EOS ; 
 int /*<<< orphan*/  CMD_PAUSE ; 
 int EINVAL ; 
 int /*<<< orphan*/  Q6ASM_STREAM_STOPPED ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int q6asm_cmd_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6asm_run_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6asm_dai_compr_trigger(struct snd_compr_stream *stream, int cmd)
{
	struct snd_compr_runtime *runtime = stream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = q6asm_run_nowait(prtd->audio_client, 0, 0, 0);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		prtd->state = Q6ASM_STREAM_STOPPED;
		ret = q6asm_cmd_nowait(prtd->audio_client, CMD_EOS);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = q6asm_cmd_nowait(prtd->audio_client, CMD_PAUSE);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}