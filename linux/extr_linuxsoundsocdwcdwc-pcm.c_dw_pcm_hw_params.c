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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct dw_i2s_dev* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct dw_i2s_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_fn; int /*<<< orphan*/  tx_fn; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_pcm_rx_16 ; 
 int /*<<< orphan*/  dw_pcm_rx_32 ; 
 int /*<<< orphan*/  dw_pcm_tx_16 ; 
 int /*<<< orphan*/  dw_pcm_tx_32 ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_pcm_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *hw_params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct dw_i2s_dev *dev = runtime->private_data;
	int ret;

	switch (params_channels(hw_params)) {
	case 2:
		break;
	default:
		dev_err(dev->dev, "invalid channels number\n");
		return -EINVAL;
	}

	switch (params_format(hw_params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		dev->tx_fn = dw_pcm_tx_16;
		dev->rx_fn = dw_pcm_rx_16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S32_LE:
		dev->tx_fn = dw_pcm_tx_32;
		dev->rx_fn = dw_pcm_rx_32;
		break;
	default:
		dev_err(dev->dev, "invalid format\n");
		return -EINVAL;
	}

	ret = snd_pcm_lib_malloc_pages(substream,
			params_buffer_bytes(hw_params));
	if (ret < 0)
		return ret;
	else
		return 0;
}