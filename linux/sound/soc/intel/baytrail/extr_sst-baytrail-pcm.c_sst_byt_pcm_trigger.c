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
struct sst_byt_priv_data {int restore_stream; struct sst_byt* byt; struct sst_byt_pcm_data* pcm; } ;
struct sst_byt_pcm_data {int /*<<< orphan*/  stream; int /*<<< orphan*/  work; int /*<<< orphan*/  hw_ptr; } ;
struct sst_byt {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct sst_byt_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_stream_pause (struct sst_byt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_stream_resume (struct sst_byt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_stream_start (struct sst_byt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_stream_stop (struct sst_byt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_byt_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_byt_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_byt_pcm_data *pcm_data = &pdata->pcm[substream->stream];
	struct sst_byt *byt = pdata->byt;

	dev_dbg(rtd->dev, "PCM: trigger %d\n", cmd);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		pcm_data->hw_ptr = 0;
		sst_byt_stream_start(byt, pcm_data->stream, 0);
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
		if (pdata->restore_stream)
			schedule_work(&pcm_data->work);
		else
			sst_byt_stream_resume(byt, pcm_data->stream);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		sst_byt_stream_resume(byt, pcm_data->stream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		sst_byt_stream_stop(byt, pcm_data->stream);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		pdata->restore_stream = false;
		/* fallthrough */
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		sst_byt_stream_pause(byt, pcm_data->stream);
		break;
	default:
		break;
	}

	return 0;
}