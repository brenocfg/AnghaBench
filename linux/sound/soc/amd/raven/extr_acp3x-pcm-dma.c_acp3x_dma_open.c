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
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct i2s_stream_instance* private_data; int /*<<< orphan*/  hw; } ;
struct i2s_stream_instance {scalar_t__ acp3x_base; } ;
struct i2s_dev_data {scalar_t__ acp3x_base; struct snd_pcm_substream* capture_stream; struct snd_pcm_substream* play_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  acp3x_pcm_hardware_capture ; 
 int /*<<< orphan*/  acp3x_pcm_hardware_playback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct i2s_dev_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2s_stream_instance*) ; 
 struct i2s_stream_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmACP_EXTERNAL_INTR_ENB ; 
 int /*<<< orphan*/  rv_writel (int,scalar_t__) ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp3x_dma_open(struct snd_pcm_substream *substream)
{
	int ret = 0;

	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *prtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(prtd,
								    DRV_NAME);
	struct i2s_dev_data *adata = dev_get_drvdata(component->dev);

	struct i2s_stream_instance *i2s_data = kzalloc(sizeof(struct i2s_stream_instance),
						       GFP_KERNEL);
	if (!i2s_data)
		return -EINVAL;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		runtime->hw = acp3x_pcm_hardware_playback;
	else
		runtime->hw = acp3x_pcm_hardware_capture;

	ret = snd_pcm_hw_constraint_integer(runtime,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	if (ret < 0) {
		dev_err(component->dev, "set integer constraint failed\n");
		kfree(i2s_data);
		return ret;
	}

	if (!adata->play_stream && !adata->capture_stream)
		rv_writel(1, adata->acp3x_base + mmACP_EXTERNAL_INTR_ENB);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		adata->play_stream = substream;
	else
		adata->capture_stream = substream;

	i2s_data->acp3x_base = adata->acp3x_base;
	runtime->private_data = i2s_data;
	return 0;
}