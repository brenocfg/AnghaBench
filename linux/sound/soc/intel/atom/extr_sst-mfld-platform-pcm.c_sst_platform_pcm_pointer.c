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
struct pcm_stream_info {int buffer_ptr; int /*<<< orphan*/  pcm_delay; } ;
struct sst_runtime_stream {TYPE_1__* ops; struct pcm_stream_info stream_info; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  delay; struct sst_runtime_stream* private_data; } ;
struct TYPE_4__ {int (* stream_read_tstamp ) (int /*<<< orphan*/ ,struct pcm_stream_info*) ;} ;

/* Variables and functions */
 int SST_PLATFORM_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* sst ; 
 int sst_get_stream_status (struct sst_runtime_stream*) ; 
 int stub1 (int /*<<< orphan*/ ,struct pcm_stream_info*) ; 

__attribute__((used)) static snd_pcm_uframes_t sst_platform_pcm_pointer
			(struct snd_pcm_substream *substream)
{
	struct sst_runtime_stream *stream;
	int ret_val, status;
	struct pcm_stream_info *str_info;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	stream = substream->runtime->private_data;
	status = sst_get_stream_status(stream);
	if (status == SST_PLATFORM_INIT)
		return 0;
	str_info = &stream->stream_info;
	ret_val = stream->ops->stream_read_tstamp(sst->dev, str_info);
	if (ret_val) {
		dev_err(rtd->dev, "sst: error code = %d\n", ret_val);
		return ret_val;
	}
	substream->runtime->delay = str_info->pcm_delay;
	return str_info->buffer_ptr;
}