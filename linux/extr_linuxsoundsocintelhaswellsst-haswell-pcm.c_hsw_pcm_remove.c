#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct hsw_priv_data {int /*<<< orphan*/ ** dmab; } ;
struct TYPE_5__ {scalar_t__ channels_min; } ;
struct TYPE_6__ {scalar_t__ channels_min; } ;
struct TYPE_7__ {TYPE_1__ capture; TYPE_2__ playback; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_3__* hsw_dais ; 
 int /*<<< orphan*/  hsw_pcm_free_modules (struct hsw_priv_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void hsw_pcm_remove(struct snd_soc_component *component)
{
	struct hsw_priv_data *priv_data =
		snd_soc_component_get_drvdata(component);
	int i;

	pm_runtime_disable(component->dev);
	hsw_pcm_free_modules(priv_data);

	for (i = 0; i < ARRAY_SIZE(hsw_dais); i++) {
		if (hsw_dais[i].playback.channels_min)
			snd_dma_free_pages(&priv_data->dmab[i][0]);
		if (hsw_dais[i].capture.channels_min)
			snd_dma_free_pages(&priv_data->dmab[i][1]);
	}
}