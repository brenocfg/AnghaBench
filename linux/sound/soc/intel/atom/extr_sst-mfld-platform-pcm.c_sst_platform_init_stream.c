#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sfreq; scalar_t__ buffer_ptr; struct snd_pcm_substream* arg; int /*<<< orphan*/  period_elapsed; } ;
struct sst_runtime_stream {TYPE_3__ stream_info; TYPE_2__* ops; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_1__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int (* stream_init ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  rate; struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_PLATFORM_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* sst ; 
 int /*<<< orphan*/  sst_period_elapsed ; 
 int /*<<< orphan*/  sst_set_stream_status (struct sst_runtime_stream*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int sst_platform_init_stream(struct snd_pcm_substream *substream)
{
	struct sst_runtime_stream *stream =
			substream->runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int ret_val;

	dev_dbg(rtd->dev, "setting buffer ptr param\n");
	sst_set_stream_status(stream, SST_PLATFORM_INIT);
	stream->stream_info.period_elapsed = sst_period_elapsed;
	stream->stream_info.arg = substream;
	stream->stream_info.buffer_ptr = 0;
	stream->stream_info.sfreq = substream->runtime->rate;
	ret_val = stream->ops->stream_init(sst->dev, &stream->stream_info);
	if (ret_val)
		dev_err(rtd->dev, "control_set ret error %d\n", ret_val);
	return ret_val;

}