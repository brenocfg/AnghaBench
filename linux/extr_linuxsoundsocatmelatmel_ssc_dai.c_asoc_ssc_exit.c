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
 int /*<<< orphan*/  atmel_pcm_dma_platform_unregister (struct device*) ; 
 int /*<<< orphan*/  atmel_pcm_pdc_platform_unregister (struct device*) ; 
 struct ssc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (struct device*) ; 

__attribute__((used)) static void asoc_ssc_exit(struct device *dev)
{
	struct ssc_device *ssc = dev_get_drvdata(dev);

	if (ssc->pdata->use_dma)
		atmel_pcm_dma_platform_unregister(dev);
	else
		atmel_pcm_pdc_platform_unregister(dev);

	snd_soc_unregister_component(dev);
}