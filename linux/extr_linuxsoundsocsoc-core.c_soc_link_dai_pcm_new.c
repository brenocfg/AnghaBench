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
struct snd_soc_dai_driver {int (* pcm_new ) (struct snd_soc_pcm_runtime*,struct snd_soc_dai*) ;} ;
struct snd_soc_dai {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct snd_soc_dai_driver* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct snd_soc_pcm_runtime*,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_link_dai_pcm_new(struct snd_soc_dai **dais, int num_dais,
				struct snd_soc_pcm_runtime *rtd)
{
	int i, ret = 0;

	for (i = 0; i < num_dais; ++i) {
		struct snd_soc_dai_driver *drv = dais[i]->driver;

		if (!rtd->dai_link->no_pcm && drv->pcm_new)
			ret = drv->pcm_new(rtd, dais[i]);
		if (ret < 0) {
			dev_err(dais[i]->dev,
				"ASoC: Failed to bind %s with pcm device\n",
				dais[i]->name);
			return ret;
		}
	}

	return 0;
}