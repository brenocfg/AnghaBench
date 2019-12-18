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
struct soc_tplg {TYPE_1__* comp; int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_stream_caps {int dummy; } ;
struct snd_soc_tplg_dai {scalar_t__ flags; scalar_t__ flag_mask; struct snd_soc_tplg_stream_caps* caps; scalar_t__ capture; scalar_t__ playback; int /*<<< orphan*/  dai_name; scalar_t__ dai_id; } ;
struct snd_soc_pcm_stream {int dummy; } ;
struct snd_soc_dai_link_component {int /*<<< orphan*/  dai_name; } ;
struct snd_soc_dai_driver {struct snd_soc_pcm_stream capture; struct snd_soc_pcm_stream playback; } ;
struct snd_soc_dai {scalar_t__ id; struct snd_soc_dai_driver* driver; } ;
typedef  int /*<<< orphan*/  dai_component ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SND_SOC_TPLG_STREAM_CAPTURE ; 
 size_t SND_SOC_TPLG_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct snd_soc_dai_link_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dai_flags (struct snd_soc_dai_driver*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_stream_info (struct snd_soc_pcm_stream*,struct snd_soc_tplg_stream_caps*) ; 
 struct snd_soc_dai* snd_soc_find_dai (struct snd_soc_dai_link_component*) ; 
 int soc_tplg_dai_load (struct soc_tplg*,struct snd_soc_dai_driver*,int /*<<< orphan*/ *,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_tplg_dai_config(struct soc_tplg *tplg,
			       struct snd_soc_tplg_dai *d)
{
	struct snd_soc_dai_link_component dai_component;
	struct snd_soc_dai *dai;
	struct snd_soc_dai_driver *dai_drv;
	struct snd_soc_pcm_stream *stream;
	struct snd_soc_tplg_stream_caps *caps;
	int ret;

	memset(&dai_component, 0, sizeof(dai_component));

	dai_component.dai_name = d->dai_name;
	dai = snd_soc_find_dai(&dai_component);
	if (!dai) {
		dev_err(tplg->dev, "ASoC: physical DAI %s not registered\n",
			d->dai_name);
		return -EINVAL;
	}

	if (le32_to_cpu(d->dai_id) != dai->id) {
		dev_err(tplg->dev, "ASoC: physical DAI %s id mismatch\n",
			d->dai_name);
		return -EINVAL;
	}

	dai_drv = dai->driver;
	if (!dai_drv)
		return -EINVAL;

	if (d->playback) {
		stream = &dai_drv->playback;
		caps = &d->caps[SND_SOC_TPLG_STREAM_PLAYBACK];
		set_stream_info(stream, caps);
	}

	if (d->capture) {
		stream = &dai_drv->capture;
		caps = &d->caps[SND_SOC_TPLG_STREAM_CAPTURE];
		set_stream_info(stream, caps);
	}

	if (d->flag_mask)
		set_dai_flags(dai_drv,
			      le32_to_cpu(d->flag_mask),
			      le32_to_cpu(d->flags));

	/* pass control to component driver for optional further init */
	ret = soc_tplg_dai_load(tplg, dai_drv, NULL, dai);
	if (ret < 0) {
		dev_err(tplg->comp->dev, "ASoC: DAI loading failed\n");
		return ret;
	}

	return 0;
}