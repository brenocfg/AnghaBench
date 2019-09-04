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
struct soc_tplg {int /*<<< orphan*/  index; scalar_t__ comp; TYPE_1__* ops; } ;
struct snd_soc_tplg_pcm {int dummy; } ;
struct snd_soc_dai_driver {int dummy; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {int (* dai_load ) (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dai_driver*,struct snd_soc_tplg_pcm*,struct snd_soc_dai*) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__,int /*<<< orphan*/ ,struct snd_soc_dai_driver*,struct snd_soc_tplg_pcm*,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_tplg_dai_load(struct soc_tplg *tplg,
	struct snd_soc_dai_driver *dai_drv,
	struct snd_soc_tplg_pcm *pcm, struct snd_soc_dai *dai)
{
	if (tplg->comp && tplg->ops && tplg->ops->dai_load)
		return tplg->ops->dai_load(tplg->comp, tplg->index, dai_drv,
			pcm, dai);

	return 0;
}