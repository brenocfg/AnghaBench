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
struct q6afe_i2s_cfg {int /*<<< orphan*/  sd_line_mask; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; } ;
struct q6afe_dai_data {TYPE_1__* priv; TYPE_2__* port_config; } ;
struct TYPE_4__ {struct q6afe_i2s_cfg i2s_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd_line_mask; } ;

/* Variables and functions */
 struct q6afe_dai_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_width (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int q6i2s_hw_params(struct snd_pcm_substream *substream,
			   struct snd_pcm_hw_params *params,
			   struct snd_soc_dai *dai)
{
	struct q6afe_dai_data *dai_data = dev_get_drvdata(dai->dev);
	struct q6afe_i2s_cfg *i2s = &dai_data->port_config[dai->id].i2s_cfg;

	i2s->sample_rate = params_rate(params);
	i2s->bit_width = params_width(params);
	i2s->num_channels = params_channels(params);
	i2s->sd_line_mask = dai_data->priv[dai->id].sd_line_mask;

	return 0;
}