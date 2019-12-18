#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_8__* card; TYPE_7__* dpcm; TYPE_6__* dai_link; struct snd_soc_dai* cpu_dai; TYPE_2__* pcm; } ;
struct snd_soc_dai {TYPE_4__* driver; } ;
struct snd_pcm_substream {size_t stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_compr_stream {size_t direction; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_compr_params {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_15__ {int /*<<< orphan*/  runtime_update; int /*<<< orphan*/  state; int /*<<< orphan*/  hw_params; } ;
struct TYPE_14__ {TYPE_5__* compr_ops; } ;
struct TYPE_13__ {int (* set_params ) (struct snd_compr_stream*) ;} ;
struct TYPE_12__ {TYPE_3__* cops; } ;
struct TYPE_11__ {int (* set_params ) (struct snd_compr_stream*,struct snd_compr_params*,struct snd_soc_dai*) ;} ;
struct TYPE_10__ {TYPE_1__* streams; } ;
struct TYPE_9__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 size_t SND_COMPRESS_PLAYBACK ; 
 int /*<<< orphan*/  SND_SOC_CARD_CLASS_RUNTIME ; 
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_START ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_PREPARE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_FE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_NO ; 
 int dpcm_be_dai_hw_params (struct snd_soc_pcm_runtime*,int) ; 
 int dpcm_be_dai_prepare (struct snd_soc_pcm_runtime*,int) ; 
 int /*<<< orphan*/  dpcm_dapm_stream_event (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int soc_compr_components_set_params (struct snd_compr_stream*,struct snd_compr_params*) ; 
 int stub1 (struct snd_compr_stream*,struct snd_compr_params*,struct snd_soc_dai*) ; 
 int stub2 (struct snd_compr_stream*) ; 

__attribute__((used)) static int soc_compr_set_params_fe(struct snd_compr_stream *cstream,
				   struct snd_compr_params *params)
{
	struct snd_soc_pcm_runtime *fe = cstream->private_data;
	struct snd_pcm_substream *fe_substream =
		 fe->pcm->streams[cstream->direction].substream;
	struct snd_soc_dai *cpu_dai = fe->cpu_dai;
	int ret, stream;

	if (cstream->direction == SND_COMPRESS_PLAYBACK)
		stream = SNDRV_PCM_STREAM_PLAYBACK;
	else
		stream = SNDRV_PCM_STREAM_CAPTURE;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	/*
	 * Create an empty hw_params for the BE as the machine driver must
	 * fix this up to match DSP decoder and ASRC configuration.
	 * I.e. machine driver fixup for compressed BE is mandatory.
	 */
	memset(&fe->dpcm[fe_substream->stream].hw_params, 0,
		sizeof(struct snd_pcm_hw_params));

	fe->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_FE;

	ret = dpcm_be_dai_hw_params(fe, stream);
	if (ret < 0)
		goto out;

	ret = dpcm_be_dai_prepare(fe, stream);
	if (ret < 0)
		goto out;

	if (cpu_dai->driver->cops && cpu_dai->driver->cops->set_params) {
		ret = cpu_dai->driver->cops->set_params(cstream, params, cpu_dai);
		if (ret < 0)
			goto out;
	}

	ret = soc_compr_components_set_params(cstream, params);
	if (ret < 0)
		goto out;

	if (fe->dai_link->compr_ops && fe->dai_link->compr_ops->set_params) {
		ret = fe->dai_link->compr_ops->set_params(cstream);
		if (ret < 0)
			goto out;
	}

	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_START);
	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PREPARE;

out:
	fe->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_NO;
	mutex_unlock(&fe->card->mutex);
	return ret;
}