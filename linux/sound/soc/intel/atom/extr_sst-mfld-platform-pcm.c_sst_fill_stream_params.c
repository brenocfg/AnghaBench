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
typedef  void* u8 ;
struct sst_dev_stream_map {int /*<<< orphan*/  task_id; int /*<<< orphan*/  device_id; } ;
struct sst_data {TYPE_1__* pdata; } ;
struct snd_sst_params {int stream_id; void* ops; int /*<<< orphan*/  task; int /*<<< orphan*/  device_type; int /*<<< orphan*/  stream_type; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  number; TYPE_2__* pcm; } ;
struct snd_compr_stream {scalar_t__ direction; TYPE_3__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int strm_map_size; struct sst_dev_stream_map* pdev_strm_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SST_STREAM_TYPE_MUSIC ; 
 int sst_get_stream_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct sst_dev_stream_map*,int) ; 

int sst_fill_stream_params(void *substream,
	const struct sst_data *ctx, struct snd_sst_params *str_params, bool is_compress)
{
	int map_size;
	int index;
	struct sst_dev_stream_map *map;
	struct snd_pcm_substream *pstream = NULL;
	struct snd_compr_stream *cstream = NULL;

	map = ctx->pdata->pdev_strm_map;
	map_size = ctx->pdata->strm_map_size;

	if (is_compress)
		cstream = (struct snd_compr_stream *)substream;
	else
		pstream = (struct snd_pcm_substream *)substream;

	str_params->stream_type = SST_STREAM_TYPE_MUSIC;

	/* For pcm streams */
	if (pstream) {
		index = sst_get_stream_mapping(pstream->pcm->device,
					  pstream->number, pstream->stream,
					  map, map_size);
		if (index <= 0)
			return -EINVAL;

		str_params->stream_id = index;
		str_params->device_type = map[index].device_id;
		str_params->task = map[index].task_id;

		str_params->ops = (u8)pstream->stream;
	}

	if (cstream) {
		index = sst_get_stream_mapping(cstream->device->device,
					       0, cstream->direction,
					       map, map_size);
		if (index <= 0)
			return -EINVAL;
		str_params->stream_id = index;
		str_params->device_type = map[index].device_id;
		str_params->task = map[index].task_id;

		str_params->ops = (u8)cstream->direction;
	}
	return 0;
}