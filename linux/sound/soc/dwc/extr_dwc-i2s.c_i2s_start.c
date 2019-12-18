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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct i2s_clk_config_data {int /*<<< orphan*/  chan_nr; } ;
struct dw_i2s_dev {int /*<<< orphan*/  i2s_base; struct i2s_clk_config_data config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CER ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IRER ; 
 int /*<<< orphan*/  ITER ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  i2s_enable_irqs (struct dw_i2s_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i2s_start(struct dw_i2s_dev *dev,
		      struct snd_pcm_substream *substream)
{
	struct i2s_clk_config_data *config = &dev->config;

	i2s_write_reg(dev->i2s_base, IER, 1);
	i2s_enable_irqs(dev, substream->stream, config->chan_nr);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		i2s_write_reg(dev->i2s_base, ITER, 1);
	else
		i2s_write_reg(dev->i2s_base, IRER, 1);

	i2s_write_reg(dev->i2s_base, CER, 1);
}