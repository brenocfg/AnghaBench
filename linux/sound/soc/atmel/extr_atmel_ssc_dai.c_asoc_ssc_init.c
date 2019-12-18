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
struct ssc_device {TYPE_1__* pdata; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ use_dma; } ;

/* Variables and functions */
 int atmel_pcm_dma_platform_register (struct device*) ; 
 int atmel_pcm_pdc_platform_register (struct device*) ; 
 int /*<<< orphan*/  atmel_ssc_component ; 
 int /*<<< orphan*/  atmel_ssc_dai ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ssc_device* dev_get_drvdata (struct device*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int asoc_ssc_init(struct device *dev)
{
	struct ssc_device *ssc = dev_get_drvdata(dev);
	int ret;

	ret = devm_snd_soc_register_component(dev, &atmel_ssc_component,
					 &atmel_ssc_dai, 1);
	if (ret) {
		dev_err(dev, "Could not register DAI: %d\n", ret);
		return ret;
	}

	if (ssc->pdata->use_dma)
		ret = atmel_pcm_dma_platform_register(dev);
	else
		ret = atmel_pcm_pdc_platform_register(dev);

	if (ret) {
		dev_err(dev, "Could not register PCM: %d\n", ret);
		return ret;
	}

	return 0;
}