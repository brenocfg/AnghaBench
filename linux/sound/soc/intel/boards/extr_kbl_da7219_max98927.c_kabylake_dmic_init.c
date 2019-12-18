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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dapm_ignore_suspend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int kabylake_dmic_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	ret = snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");
	if (ret)
		dev_err(rtd->dev, "SoC DMIC - Ignore suspend failed %d\n", ret);

	return ret;
}