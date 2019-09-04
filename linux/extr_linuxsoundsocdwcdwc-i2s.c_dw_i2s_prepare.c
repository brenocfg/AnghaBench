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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct dw_i2s_dev {int /*<<< orphan*/  i2s_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXFFR ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TXFFR ; 
 int /*<<< orphan*/  i2s_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dw_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int dw_i2s_prepare(struct snd_pcm_substream *substream,
			  struct snd_soc_dai *dai)
{
	struct dw_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		i2s_write_reg(dev->i2s_base, TXFFR, 1);
	else
		i2s_write_reg(dev->i2s_base, RXFFR, 1);

	return 0;
}