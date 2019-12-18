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
typedef  int u8 ;
struct xen_snd_front_pcm_stream_info {int is_open; int /*<<< orphan*/  shbuf; TYPE_3__* evt_pair; TYPE_2__* front_info; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; } ;
struct TYPE_6__ {int /*<<< orphan*/  req; } ;
struct TYPE_5__ {TYPE_1__* xb_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int to_sndif_format (int /*<<< orphan*/ ) ; 
 int xen_snd_front_stream_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alsa_prepare(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	if (!stream->is_open) {
		struct snd_pcm_runtime *runtime = substream->runtime;
		u8 sndif_format;
		int ret;

		ret = to_sndif_format(runtime->format);
		if (ret < 0) {
			dev_err(&stream->front_info->xb_dev->dev,
				"Unsupported sample format: %d\n",
				runtime->format);
			return ret;
		}
		sndif_format = ret;

		ret = xen_snd_front_stream_prepare(&stream->evt_pair->req,
						   &stream->shbuf,
						   sndif_format,
						   runtime->channels,
						   runtime->rate,
						   snd_pcm_lib_buffer_bytes(substream),
						   snd_pcm_lib_period_bytes(substream));
		if (ret < 0)
			return ret;

		stream->is_open = true;
	}

	return 0;
}