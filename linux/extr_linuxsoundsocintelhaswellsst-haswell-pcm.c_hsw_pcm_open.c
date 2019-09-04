#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_hsw {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_1__* cpu_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;
struct hsw_priv_data {int /*<<< orphan*/  dev; struct hsw_pcm_data** pcm; struct sst_hsw* hsw; } ;
struct hsw_pcm_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * stream; struct snd_pcm_substream* substream; } ;
struct TYPE_4__ {int dai_id; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hsw_notify_pointer ; 
 int /*<<< orphan*/  hsw_pcm_hardware ; 
 TYPE_2__* mod_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sst_hsw_stream_new (struct sst_hsw*,size_t,int /*<<< orphan*/ ,struct hsw_pcm_data*) ; 

__attribute__((used)) static int hsw_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct hsw_pcm_data *pcm_data;
	struct sst_hsw *hsw = pdata->hsw;
	int dai;

	dai = mod_map[rtd->cpu_dai->id].dai_id;
	pcm_data = &pdata->pcm[dai][substream->stream];

	mutex_lock(&pcm_data->mutex);
	pm_runtime_get_sync(pdata->dev);

	pcm_data->substream = substream;

	snd_soc_set_runtime_hwparams(substream, &hsw_pcm_hardware);

	pcm_data->stream = sst_hsw_stream_new(hsw, rtd->cpu_dai->id,
		hsw_notify_pointer, pcm_data);
	if (pcm_data->stream == NULL) {
		dev_err(rtd->dev, "error: failed to create stream\n");
		pm_runtime_mark_last_busy(pdata->dev);
		pm_runtime_put_autosuspend(pdata->dev);
		mutex_unlock(&pcm_data->mutex);
		return -EINVAL;
	}

	mutex_unlock(&pcm_data->mutex);
	return 0;
}