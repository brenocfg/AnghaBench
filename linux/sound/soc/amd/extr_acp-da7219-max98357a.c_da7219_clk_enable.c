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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  da7219_dai_bclk ; 
 int /*<<< orphan*/  da7219_dai_wclk ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int da7219_clk_enable(struct snd_pcm_substream *substream,
			     int wclk_rate, int bclk_rate)
{
	int ret = 0;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	clk_set_rate(da7219_dai_wclk, wclk_rate);
	clk_set_rate(da7219_dai_bclk, bclk_rate);
	ret = clk_prepare_enable(da7219_dai_bclk);
	if (ret < 0) {
		dev_err(rtd->dev, "can't enable master clock %d\n", ret);
		return ret;
	}

	return ret;
}