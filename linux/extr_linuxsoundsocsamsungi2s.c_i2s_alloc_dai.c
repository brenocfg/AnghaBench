#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct samsung_i2s_dai_data {int /*<<< orphan*/  pcm_rates; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int channels_min; int channels_max; void* formats; int /*<<< orphan*/  rates; } ;
struct TYPE_4__ {int channels_min; int channels_max; void* formats; int /*<<< orphan*/  rates; } ;
struct TYPE_6__ {int id; int symmetric_rates; int /*<<< orphan*/  name; TYPE_2__ capture; TYPE_1__ playback; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/ * ops; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;
struct i2s_dai {TYPE_3__ i2s_dai_drv; int /*<<< orphan*/ * sec_dai; int /*<<< orphan*/ * pri_dai; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAMSUNG_I2S_DAI ; 
 int /*<<< orphan*/  SAMSUNG_I2S_DAI_SEC ; 
 void* SAMSUNG_I2S_FMTS ; 
 struct i2s_dai* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_resume ; 
 int /*<<< orphan*/  i2s_suspend ; 
 int /*<<< orphan*/  samsung_i2s_dai_ops ; 
 int /*<<< orphan*/  samsung_i2s_dai_probe ; 
 int /*<<< orphan*/  samsung_i2s_dai_remove ; 

__attribute__((used)) static struct i2s_dai *i2s_alloc_dai(struct platform_device *pdev,
				const struct samsung_i2s_dai_data *i2s_dai_data,
				bool sec)
{
	struct i2s_dai *i2s;

	i2s = devm_kzalloc(&pdev->dev, sizeof(struct i2s_dai), GFP_KERNEL);
	if (i2s == NULL)
		return NULL;

	i2s->pdev = pdev;
	i2s->pri_dai = NULL;
	i2s->sec_dai = NULL;
	i2s->i2s_dai_drv.id = 1;
	i2s->i2s_dai_drv.symmetric_rates = 1;
	i2s->i2s_dai_drv.probe = samsung_i2s_dai_probe;
	i2s->i2s_dai_drv.remove = samsung_i2s_dai_remove;
	i2s->i2s_dai_drv.ops = &samsung_i2s_dai_ops;
	i2s->i2s_dai_drv.suspend = i2s_suspend;
	i2s->i2s_dai_drv.resume = i2s_resume;
	i2s->i2s_dai_drv.playback.channels_min = 1;
	i2s->i2s_dai_drv.playback.channels_max = 2;
	i2s->i2s_dai_drv.playback.rates = i2s_dai_data->pcm_rates;
	i2s->i2s_dai_drv.playback.formats = SAMSUNG_I2S_FMTS;

	if (!sec) {
		i2s->i2s_dai_drv.name = SAMSUNG_I2S_DAI;
		i2s->i2s_dai_drv.capture.channels_min = 1;
		i2s->i2s_dai_drv.capture.channels_max = 2;
		i2s->i2s_dai_drv.capture.rates = i2s_dai_data->pcm_rates;
		i2s->i2s_dai_drv.capture.formats = SAMSUNG_I2S_FMTS;
	} else {
		i2s->i2s_dai_drv.name = SAMSUNG_I2S_DAI_SEC;
	}
	return i2s;
}