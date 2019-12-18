#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_hsw {int dummy; } ;
struct hsw_priv_data {int /*<<< orphan*/ * runtime_waves; struct hsw_pcm_data** pcm; struct sst_hsw* hsw; } ;
struct hsw_pcm_data {int /*<<< orphan*/ * runtime; } ;
struct TYPE_3__ {size_t dai_id; size_t stream; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SST_HSW_MODULE_WAVES ; 
 TYPE_1__* mod_map ; 
 scalar_t__ sst_hsw_is_module_loaded (struct sst_hsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_hsw_runtime_module_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsw_pcm_free_modules(struct hsw_priv_data *pdata)
{
	struct sst_hsw *hsw = pdata->hsw;
	struct hsw_pcm_data *pcm_data;
	int i;

	for (i = 0; i < ARRAY_SIZE(mod_map); i++) {
		pcm_data = &pdata->pcm[mod_map[i].dai_id][mod_map[i].stream];
		if (pcm_data->runtime){
			sst_hsw_runtime_module_free(pcm_data->runtime);
			pcm_data->runtime = NULL;
		}
	}
	if (sst_hsw_is_module_loaded(hsw, SST_HSW_MODULE_WAVES) &&
				pdata->runtime_waves) {
		sst_hsw_runtime_module_free(pdata->runtime_waves);
		pdata->runtime_waves = NULL;
	}
}