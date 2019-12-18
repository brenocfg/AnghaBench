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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_compr_stream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * adsp; struct arizona* arizona; } ;
struct cs47l24_priv {TYPE_2__ core; } ;
struct arizona {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cs47l24_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int wm_adsp_compr_open (int /*<<< orphan*/ *,struct snd_compr_stream*) ; 

__attribute__((used)) static int cs47l24_open(struct snd_compr_stream *stream)
{
	struct snd_soc_pcm_runtime *rtd = stream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct cs47l24_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->core.arizona;
	int n_adsp;

	if (strcmp(rtd->codec_dai->name, "cs47l24-dsp-voicectrl") == 0) {
		n_adsp = 2;
	} else if (strcmp(rtd->codec_dai->name, "cs47l24-dsp-trace") == 0) {
		n_adsp = 1;
	} else {
		dev_err(arizona->dev,
			"No suitable compressed stream for DAI '%s'\n",
			rtd->codec_dai->name);
		return -EINVAL;
	}

	return wm_adsp_compr_open(&priv->core.adsp[n_adsp], stream);
}