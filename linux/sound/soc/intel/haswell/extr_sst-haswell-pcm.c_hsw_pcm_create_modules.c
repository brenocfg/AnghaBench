#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sst_hsw {int dummy; } ;
struct hsw_priv_data {struct hsw_pcm_data** pcm; int /*<<< orphan*/ * runtime_waves; struct sst_hsw* hsw; } ;
struct hsw_pcm_data {TYPE_1__* runtime; int /*<<< orphan*/  persistent_offset; } ;
struct TYPE_5__ {size_t dai_id; size_t stream; int /*<<< orphan*/  mod_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  persistent_offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  SST_HSW_MODULE_WAVES ; 
 TYPE_2__* mod_map ; 
 scalar_t__ sst_hsw_is_module_loaded (struct sst_hsw*,int /*<<< orphan*/ ) ; 
 void* sst_hsw_runtime_module_create (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_hsw_runtime_module_free (TYPE_1__*) ; 

__attribute__((used)) static int hsw_pcm_create_modules(struct hsw_priv_data *pdata)
{
	struct sst_hsw *hsw = pdata->hsw;
	struct hsw_pcm_data *pcm_data;
	int i;

	for (i = 0; i < ARRAY_SIZE(mod_map); i++) {
		pcm_data = &pdata->pcm[mod_map[i].dai_id][mod_map[i].stream];

		/* create new runtime module, use same offset if recreated */
		pcm_data->runtime = sst_hsw_runtime_module_create(hsw,
			mod_map[i].mod_id, pcm_data->persistent_offset);
		if (pcm_data->runtime == NULL)
			goto err;
		pcm_data->persistent_offset =
			pcm_data->runtime->persistent_offset;
	}

	/* create runtime blocks for module waves */
	if (sst_hsw_is_module_loaded(hsw, SST_HSW_MODULE_WAVES)) {
		pdata->runtime_waves = sst_hsw_runtime_module_create(hsw,
			SST_HSW_MODULE_WAVES, 0);
		if (pdata->runtime_waves == NULL)
			goto err;
	}

	return 0;

err:
	for (--i; i >= 0; i--) {
		pcm_data = &pdata->pcm[mod_map[i].dai_id][mod_map[i].stream];
		sst_hsw_runtime_module_free(pcm_data->runtime);
	}

	return -ENODEV;
}