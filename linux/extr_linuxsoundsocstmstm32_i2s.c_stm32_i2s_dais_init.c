#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stm32_i2s_data {struct snd_soc_dai_driver* dai_drv; int /*<<< orphan*/  dais_name; } ;
struct snd_soc_dai_driver {int id; int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  probe; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STM32_I2S_DAI_NAME_SIZE ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct snd_soc_dai_driver* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stm32_i2s_dai_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stm32_i2s_dai_probe ; 
 int /*<<< orphan*/  stm32_i2s_pcm_dai_ops ; 

__attribute__((used)) static int stm32_i2s_dais_init(struct platform_device *pdev,
			       struct stm32_i2s_data *i2s)
{
	struct snd_soc_dai_driver *dai_ptr;

	dai_ptr = devm_kzalloc(&pdev->dev, sizeof(struct snd_soc_dai_driver),
			       GFP_KERNEL);
	if (!dai_ptr)
		return -ENOMEM;

	snprintf(i2s->dais_name, STM32_I2S_DAI_NAME_SIZE,
		 "%s", dev_name(&pdev->dev));

	dai_ptr->probe = stm32_i2s_dai_probe;
	dai_ptr->ops = &stm32_i2s_pcm_dai_ops;
	dai_ptr->name = i2s->dais_name;
	dai_ptr->id = 1;
	stm32_i2s_dai_init(&dai_ptr->playback, "playback");
	stm32_i2s_dai_init(&dai_ptr->capture, "capture");
	i2s->dai_drv = dai_ptr;

	return 0;
}