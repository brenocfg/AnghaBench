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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct q6afe_tdm_cfg {int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  sync_src; int /*<<< orphan*/  data_align_type; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  bit_width; } ;
struct q6afe_dai_data {TYPE_2__* priv; TYPE_1__* port_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  sync_src; int /*<<< orphan*/  data_align; } ;
struct TYPE_3__ {struct q6afe_tdm_cfg tdm; } ;

/* Variables and functions */
 struct q6afe_dai_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_width (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int q6tdm_hw_params(struct snd_pcm_substream *substream,
			   struct snd_pcm_hw_params *params,
			   struct snd_soc_dai *dai)
{
	struct q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	struct q6afe_tdm_cfg *tdm = &dai_data->port_config[dai->id].tdm;

	tdm->bit_width = params_width(params);
	tdm->sample_rate = params_rate(params);
	tdm->num_channels = params_channels(params);
	tdm->data_align_type = dai_data->priv[dai->id].data_align;
	tdm->sync_src = dai_data->priv[dai->id].sync_src;
	tdm->sync_mode = dai_data->priv[dai->id].sync_mode;

	return 0;
}