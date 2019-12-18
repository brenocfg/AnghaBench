#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int str_id; struct snd_pcm_substream* arg; } ;
struct sst_runtime_stream {TYPE_4__* ops; TYPE_3__ stream_info; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_2__* runtime; TYPE_1__* pcm; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int (* stream_start ) (int /*<<< orphan*/ ,int) ;int (* stream_drop ) (int /*<<< orphan*/ ,int) ;int (* stream_pause ) (int /*<<< orphan*/ ,int) ;int (* stream_pause_release ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {struct sst_runtime_stream* private_data; } ;
struct TYPE_6__ {scalar_t__ internal; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int SST_PLATFORM_DROPPED ; 
 int SST_PLATFORM_PAUSED ; 
 int SST_PLATFORM_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* sst ; 
 int /*<<< orphan*/  sst_set_stream_status (struct sst_runtime_stream*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sst_platform_pcm_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	int ret_val = 0, str_id;
	struct sst_runtime_stream *stream;
	int status;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	dev_dbg(rtd->dev, "sst_platform_pcm_trigger called\n");
	if (substream->pcm->internal)
		return 0;
	stream = substream->runtime->private_data;
	str_id = stream->stream_info.str_id;
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dev_dbg(rtd->dev, "sst: Trigger Start\n");
		status = SST_PLATFORM_RUNNING;
		stream->stream_info.arg = substream;
		ret_val = stream->ops->stream_start(sst->dev, str_id);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(rtd->dev, "sst: in stop\n");
		status = SST_PLATFORM_DROPPED;
		ret_val = stream->ops->stream_drop(sst->dev, str_id);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		dev_dbg(rtd->dev, "sst: in pause\n");
		status = SST_PLATFORM_PAUSED;
		ret_val = stream->ops->stream_pause(sst->dev, str_id);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		dev_dbg(rtd->dev, "sst: in pause release\n");
		status = SST_PLATFORM_RUNNING;
		ret_val = stream->ops->stream_pause_release(sst->dev, str_id);
		break;
	default:
		return -EINVAL;
	}

	if (!ret_val)
		sst_set_stream_status(stream, status);

	return ret_val;
}