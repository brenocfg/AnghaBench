#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sst_runtime_stream {int /*<<< orphan*/  id; TYPE_2__* compr_ops; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int (* stream_start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* stream_drop ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* stream_drain ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* stream_partial_drain ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* stream_pause ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* stream_pause_release ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_START 131 
#define  SNDRV_PCM_TRIGGER_STOP 130 
#define  SND_COMPR_TRIGGER_DRAIN 129 
#define  SND_COMPR_TRIGGER_PARTIAL_DRAIN 128 
 TYPE_3__* sst ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_platform_compr_trigger(struct snd_compr_stream *cstream, int cmd)
{
	struct sst_runtime_stream *stream = cstream->runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (stream->compr_ops->stream_start)
			return stream->compr_ops->stream_start(sst->dev, stream->id);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (stream->compr_ops->stream_drop)
			return stream->compr_ops->stream_drop(sst->dev, stream->id);
		break;
	case SND_COMPR_TRIGGER_DRAIN:
		if (stream->compr_ops->stream_drain)
			return stream->compr_ops->stream_drain(sst->dev, stream->id);
		break;
	case SND_COMPR_TRIGGER_PARTIAL_DRAIN:
		if (stream->compr_ops->stream_partial_drain)
			return stream->compr_ops->stream_partial_drain(sst->dev, stream->id);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (stream->compr_ops->stream_pause)
			return stream->compr_ops->stream_pause(sst->dev, stream->id);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (stream->compr_ops->stream_pause_release)
			return stream->compr_ops->stream_pause_release(sst->dev, stream->id);
		break;
	}
	return -EINVAL;
}