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
struct TYPE_4__ {int /*<<< orphan*/  pcm_id; } ;
struct snd_sof_pcm {int /*<<< orphan*/ * params; TYPE_2__ pcm; scalar_t__* prepared; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_3__ {scalar_t__ no_pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 
 int sof_pcm_hw_params (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sof_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pcm *spcm;
	int ret;

	/* nothing to do for BE */
	if (rtd->dai_link->no_pcm)
		return 0;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm)
		return -EINVAL;

	if (spcm->prepared[substream->stream])
		return 0;

	dev_dbg(sdev->dev, "pcm: prepare stream %d dir %d\n", spcm->pcm.pcm_id,
		substream->stream);

	/* set hw_params */
	ret = sof_pcm_hw_params(substream, &spcm->params[substream->stream]);
	if (ret < 0) {
		dev_err(sdev->dev, "error: set pcm hw_params after resume\n");
		return ret;
	}

	return 0;
}