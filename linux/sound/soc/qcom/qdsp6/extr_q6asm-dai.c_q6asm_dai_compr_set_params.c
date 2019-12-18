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
struct snd_soc_pcm_runtime {TYPE_2__* dai_link; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_compr_stream {int direction; struct snd_soc_pcm_runtime* private_data; struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {int fragments; int fragment_size; struct q6asm_dai_rtd* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct snd_compr_params {TYPE_1__ codec; } ;
struct q6asm_dai_rtd {int periods; int pcm_count; int pcm_size; int bits_per_sample; int /*<<< orphan*/  state; int /*<<< orphan*/  phys; int /*<<< orphan*/ * audio_client; int /*<<< orphan*/  session_id; int /*<<< orphan*/  codec_param; } ;
struct q6asm_dai_data {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LEGACY_PCM_MODE ; 
 int /*<<< orphan*/  Q6ASM_STREAM_RUNNING ; 
 int SND_COMPRESS_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct snd_compr_params*,int) ; 
 int /*<<< orphan*/  q6asm_audio_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q6asm_get_session_id (int /*<<< orphan*/ *) ; 
 int q6asm_map_memory_regions (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int q6asm_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int q6routing_stream_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct q6asm_dai_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6asm_dai_compr_set_params(struct snd_compr_stream *stream,
				      struct snd_compr_params *params)
{
	struct snd_compr_runtime *runtime = stream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = stream->private_data;
	struct snd_soc_component *c = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	int dir = stream->direction;
	struct q6asm_dai_data *pdata;
	struct device *dev = c->dev;
	int ret;

	memcpy(&prtd->codec_param, params, sizeof(*params));

	pdata = snd_soc_component_get_drvdata(c);
	if (!pdata)
		return -EINVAL;

	if (!prtd || !prtd->audio_client) {
		dev_err(dev, "private data null or audio client freed\n");
		return -EINVAL;
	}

	prtd->periods = runtime->fragments;
	prtd->pcm_count = runtime->fragment_size;
	prtd->pcm_size = runtime->fragments * runtime->fragment_size;
	prtd->bits_per_sample = 16;
	if (dir == SND_COMPRESS_PLAYBACK) {
		ret = q6asm_open_write(prtd->audio_client, params->codec.id,
					prtd->bits_per_sample);

		if (ret < 0) {
			dev_err(dev, "q6asm_open_write failed\n");
			q6asm_audio_client_free(prtd->audio_client);
			prtd->audio_client = NULL;
			return ret;
		}
	}

	prtd->session_id = q6asm_get_session_id(prtd->audio_client);
	ret = q6routing_stream_open(rtd->dai_link->id, LEGACY_PCM_MODE,
			      prtd->session_id, dir);
	if (ret) {
		dev_err(dev, "Stream reg failed ret:%d\n", ret);
		return ret;
	}

	ret = q6asm_map_memory_regions(dir, prtd->audio_client, prtd->phys,
				       (prtd->pcm_size / prtd->periods),
				       prtd->periods);

	if (ret < 0) {
		dev_err(dev, "Buffer Mapping failed ret:%d\n", ret);
		return -ENOMEM;
	}

	prtd->state = Q6ASM_STREAM_RUNNING;

	return 0;
}