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
struct sst_byt_priv_data {struct sst_byt* byt; struct sst_byt_pcm_data* pcm; } ;
struct sst_byt_pcm_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * stream; struct snd_pcm_substream* substream; } ;
struct sst_byt {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  byt_notify_pointer ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sst_byt_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_byt_pcm_hardware ; 
 int /*<<< orphan*/ * sst_byt_stream_new (struct sst_byt*,int,int /*<<< orphan*/ ,struct sst_byt_pcm_data*) ; 

__attribute__((used)) static int sst_byt_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_byt_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_byt_pcm_data *pcm_data = &pdata->pcm[substream->stream];
	struct sst_byt *byt = pdata->byt;

	dev_dbg(rtd->dev, "PCM: open\n");

	mutex_lock(&pcm_data->mutex);

	pcm_data->substream = substream;

	snd_soc_set_runtime_hwparams(substream, &sst_byt_pcm_hardware);

	pcm_data->stream = sst_byt_stream_new(byt, substream->stream + 1,
					      byt_notify_pointer, pcm_data);
	if (pcm_data->stream == NULL) {
		dev_err(rtd->dev, "failed to create stream\n");
		mutex_unlock(&pcm_data->mutex);
		return -EINVAL;
	}

	mutex_unlock(&pcm_data->mutex);
	return 0;
}