#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int str_id; } ;
struct sst_runtime_stream {TYPE_3__ stream_info; TYPE_1__* ops; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_5__* runtime; TYPE_2__* pcm; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  info; } ;
struct TYPE_11__ {TYPE_4__ hw; struct sst_runtime_stream* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int (* stream_drop ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_INFO_BLOCK_TRANSFER ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 TYPE_6__* sst ; 
 int sst_platform_alloc_stream (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int sst_platform_init_stream (struct snd_pcm_substream*) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sst_media_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct sst_runtime_stream *stream;
	int ret_val = 0, str_id;

	stream = substream->runtime->private_data;
	str_id = stream->stream_info.str_id;
	if (stream->stream_info.str_id) {
		ret_val = stream->ops->stream_drop(sst->dev, str_id);
		return ret_val;
	}

	ret_val = sst_platform_alloc_stream(substream, dai);
	if (ret_val <= 0)
		return ret_val;
	snprintf(substream->pcm->id, sizeof(substream->pcm->id),
			"%d", stream->stream_info.str_id);

	ret_val = sst_platform_init_stream(substream);
	if (ret_val)
		return ret_val;
	substream->runtime->hw.info = SNDRV_PCM_INFO_BLOCK_TRANSFER;
	return ret_val;
}