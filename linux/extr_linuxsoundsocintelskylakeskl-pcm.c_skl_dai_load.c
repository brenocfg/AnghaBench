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
struct snd_soc_tplg_pcm {int dummy; } ;
struct snd_soc_dai_driver {int /*<<< orphan*/ * ops; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_pcm_dai_ops ; 

int skl_dai_load(struct snd_soc_component *cmp, int index,
			struct snd_soc_dai_driver *dai_drv,
			struct snd_soc_tplg_pcm *pcm, struct snd_soc_dai *dai)
{
	dai_drv->ops = &skl_pcm_dai_ops;

	return 0;
}