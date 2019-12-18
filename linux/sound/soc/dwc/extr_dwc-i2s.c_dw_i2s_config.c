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
typedef  int u32 ;
struct i2s_clk_config_data {int chan_nr; } ;
struct dw_i2s_dev {int xfer_resolution; int fifo_th; int /*<<< orphan*/  i2s_base; struct i2s_clk_config_data config; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCR (int) ; 
 int /*<<< orphan*/  RER (int) ; 
 int /*<<< orphan*/  RFCR (int) ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TCR (int) ; 
 int /*<<< orphan*/  TER (int) ; 
 int /*<<< orphan*/  TFCR (int) ; 
 int /*<<< orphan*/  i2s_disable_channels (struct dw_i2s_dev*,int) ; 
 int /*<<< orphan*/  i2s_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_i2s_config(struct dw_i2s_dev *dev, int stream)
{
	u32 ch_reg;
	struct i2s_clk_config_data *config = &dev->config;


	i2s_disable_channels(dev, stream);

	for (ch_reg = 0; ch_reg < (config->chan_nr / 2); ch_reg++) {
		if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
			i2s_write_reg(dev->i2s_base, TCR(ch_reg),
				      dev->xfer_resolution);
			i2s_write_reg(dev->i2s_base, TFCR(ch_reg),
				      dev->fifo_th - 1);
			i2s_write_reg(dev->i2s_base, TER(ch_reg), 1);
		} else {
			i2s_write_reg(dev->i2s_base, RCR(ch_reg),
				      dev->xfer_resolution);
			i2s_write_reg(dev->i2s_base, RFCR(ch_reg),
				      dev->fifo_th - 1);
			i2s_write_reg(dev->i2s_base, RER(ch_reg), 1);
		}

	}
}