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
struct spdif_dev_data {scalar_t__ base; int /*<<< orphan*/  aclk; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int AES_SAMPLE_WIDTH ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int MAX_CHANNELS ; 
 int XSPDIF_CLOCK_CONFIG_BITS_MASK ; 
 int XSPDIF_CLOCK_CONFIG_BITS_SHIFT ; 
 scalar_t__ XSPDIF_CONTROL_REG ; 
 struct spdif_dev_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xlnx_spdif_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	u32 val, clk_div, clk_cfg;
	struct spdif_dev_data *ctx = dev_get_drvdata(dai->dev);

	clk_div = DIV_ROUND_CLOSEST(ctx->aclk, MAX_CHANNELS * AES_SAMPLE_WIDTH *
				    params_rate(params));

	switch (clk_div) {
	case 4:
		clk_cfg = 0;
		break;
	case 8:
		clk_cfg = 1;
		break;
	case 16:
		clk_cfg = 2;
		break;
	case 24:
		clk_cfg = 3;
		break;
	case 32:
		clk_cfg = 4;
		break;
	case 48:
		clk_cfg = 5;
		break;
	case 64:
		clk_cfg = 6;
		break;
	default:
		return -EINVAL;
	}

	val = readl(ctx->base + XSPDIF_CONTROL_REG);
	val &= ~XSPDIF_CLOCK_CONFIG_BITS_MASK;
	val |= clk_cfg << XSPDIF_CLOCK_CONFIG_BITS_SHIFT;
	writel(val, ctx->base + XSPDIF_CONTROL_REG);

	return 0;
}