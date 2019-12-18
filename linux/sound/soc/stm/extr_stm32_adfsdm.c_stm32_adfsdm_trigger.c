#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32_adfsdm_priv {TYPE_1__* iio_ch; int /*<<< orphan*/  pos; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  indio_dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct stm32_adfsdm_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_afsdm_pcm_cb ; 
 int stm32_dfsdm_get_buff_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_adfsdm_priv*) ; 
 int stm32_dfsdm_release_buff_cb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_adfsdm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct stm32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(rtd->cpu_dai);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		priv->pos = 0;
		return stm32_dfsdm_get_buff_cb(priv->iio_ch->indio_dev,
					       stm32_afsdm_pcm_cb, priv);
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
		return stm32_dfsdm_release_buff_cb(priv->iio_ch->indio_dev);
	}

	return -EINVAL;
}