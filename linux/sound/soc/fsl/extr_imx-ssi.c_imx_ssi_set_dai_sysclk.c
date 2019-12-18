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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct imx_ssi {scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IMX_SSP_SYS_CLK 128 
 int SND_SOC_CLOCK_OUT ; 
 scalar_t__ SSI_SCR ; 
 int /*<<< orphan*/  SSI_SCR_SYS_CLK_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct imx_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
				  int clk_id, unsigned int freq, int dir)
{
	struct imx_ssi *ssi = snd_soc_dai_get_drvdata(cpu_dai);
	u32 scr;

	scr = readl(ssi->base + SSI_SCR);

	switch (clk_id) {
	case IMX_SSP_SYS_CLK:
		if (dir == SND_SOC_CLOCK_OUT)
			scr |= SSI_SCR_SYS_CLK_EN;
		else
			scr &= ~SSI_SCR_SYS_CLK_EN;
		break;
	default:
		return -EINVAL;
	}

	writel(scr, ssi->base + SSI_SCR);

	return 0;
}