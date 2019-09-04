#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_snd_front_pcm_stream_info {int /*<<< orphan*/  index; TYPE_1__* front_info; int /*<<< orphan*/  sh_buf; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* xb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  stream_free (struct xen_snd_front_pcm_stream_info*) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int xen_snd_front_shbuf_alloc (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alsa_hw_params(struct snd_pcm_substream *substream,
			  struct snd_pcm_hw_params *params)
{
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	int ret;

	/*
	 * This callback may be called multiple times,
	 * so free the previously allocated shared buffer if any.
	 */
	stream_free(stream);

	ret = xen_snd_front_shbuf_alloc(stream->front_info->xb_dev,
					&stream->sh_buf,
					params_buffer_bytes(params));
	if (ret < 0) {
		stream_free(stream);
		dev_err(&stream->front_info->xb_dev->dev,
			"Failed to allocate buffers for stream with index %d\n",
			stream->index);
		return ret;
	}

	return 0;
}