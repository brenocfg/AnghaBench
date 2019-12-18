#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int channels_min; int channels_max; char* stream_name; void* formats; int /*<<< orphan*/  rates; } ;
struct TYPE_5__ {int channels_min; int channels_max; char const* stream_name; void* formats; int /*<<< orphan*/  rates; } ;
struct snd_soc_dai_driver {int symmetric_rates; int id; char const* name; TYPE_4__ capture; TYPE_1__ playback; int /*<<< orphan*/ * ops; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;
struct samsung_i2s_priv {struct snd_soc_dai_driver* dai_drv; TYPE_3__* pdev; TYPE_2__* dai; } ;
struct samsung_i2s_dai_data {int /*<<< orphan*/  pcm_rates; } ;
struct i2s_dai {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_3__* pdev; struct snd_soc_dai_driver* drv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* SAMSUNG_I2S_FMTS ; 
 int SAMSUNG_I2S_ID_PRIMARY ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_resume ; 
 int /*<<< orphan*/  i2s_suspend ; 
 int /*<<< orphan*/  samsung_i2s_dai_ops ; 
 int /*<<< orphan*/  samsung_i2s_dai_probe ; 
 int /*<<< orphan*/  samsung_i2s_dai_remove ; 

__attribute__((used)) static int i2s_alloc_dais(struct samsung_i2s_priv *priv,
			  const struct samsung_i2s_dai_data *i2s_dai_data,
			  int num_dais)
{
	static const char *dai_names[] = { "samsung-i2s", "samsung-i2s-sec" };
	static const char *stream_names[] = { "Primary Playback",
					      "Secondary Playback" };
	struct snd_soc_dai_driver *dai_drv;
	struct i2s_dai *dai;
	int i;

	priv->dai = devm_kcalloc(&priv->pdev->dev, num_dais,
				     sizeof(*dai), GFP_KERNEL);
	if (!priv->dai)
		return -ENOMEM;

	priv->dai_drv = devm_kcalloc(&priv->pdev->dev, num_dais,
				     sizeof(*dai_drv), GFP_KERNEL);
	if (!priv->dai_drv)
		return -ENOMEM;

	for (i = 0; i < num_dais; i++) {
		dai_drv = &priv->dai_drv[i];

		dai_drv->probe = samsung_i2s_dai_probe;
		dai_drv->remove = samsung_i2s_dai_remove;
		dai_drv->suspend = i2s_suspend;
		dai_drv->resume = i2s_resume;

		dai_drv->symmetric_rates = 1;
		dai_drv->ops = &samsung_i2s_dai_ops;

		dai_drv->playback.channels_min = 1;
		dai_drv->playback.channels_max = 2;
		dai_drv->playback.rates = i2s_dai_data->pcm_rates;
		dai_drv->playback.formats = SAMSUNG_I2S_FMTS;
		dai_drv->playback.stream_name = stream_names[i];

		dai_drv->id = i + 1;
		dai_drv->name = dai_names[i];

		priv->dai[i].drv = &priv->dai_drv[i];
		priv->dai[i].pdev = priv->pdev;
	}

	/* Initialize capture only for the primary DAI */
	dai_drv = &priv->dai_drv[SAMSUNG_I2S_ID_PRIMARY - 1];

	dai_drv->capture.channels_min = 1;
	dai_drv->capture.channels_max = 2;
	dai_drv->capture.rates = i2s_dai_data->pcm_rates;
	dai_drv->capture.formats = SAMSUNG_I2S_FMTS;
	dai_drv->capture.stream_name = "Primary Capture";

	return 0;
}