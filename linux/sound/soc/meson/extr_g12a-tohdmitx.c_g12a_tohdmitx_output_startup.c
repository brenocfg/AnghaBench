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
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; int /*<<< orphan*/  capture_widget; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct g12a_tohdmitx_input {int /*<<< orphan*/  fmt; int /*<<< orphan*/  params; } ;
struct TYPE_2__ {int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct g12a_tohdmitx_input* g12a_tohdmitx_get_input_data (int /*<<< orphan*/ ) ; 
 int snd_soc_runtime_set_dai_fmt (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g12a_tohdmitx_output_startup(struct snd_pcm_substream *substream,
					struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct g12a_tohdmitx_input *in_data =
		g12a_tohdmitx_get_input_data(dai->capture_widget);

	if (!in_data)
		return -ENODEV;

	if (WARN_ON(!rtd->dai_link->params)) {
		dev_warn(dai->dev, "codec2codec link expected\n");
		return -EINVAL;
	}

	/* Replace link params with the input params */
	rtd->dai_link->params = &in_data->params;

	if (!in_data->fmt)
		return 0;

	return snd_soc_runtime_set_dai_fmt(rtd, in_data->fmt);
}