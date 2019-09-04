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
struct snd_soc_dai {int dummy; } ;
struct imx_ssi {scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IMX_SSI_RX_DIV_2 133 
#define  IMX_SSI_RX_DIV_PM 132 
#define  IMX_SSI_RX_DIV_PSR 131 
#define  IMX_SSI_TX_DIV_2 130 
#define  IMX_SSI_TX_DIV_PM 129 
#define  IMX_SSI_TX_DIV_PSR 128 
 scalar_t__ SSI_SRCCR ; 
 scalar_t__ SSI_STCCR ; 
 int SSI_STCCR_DIV2 ; 
 int SSI_STCCR_PM (int) ; 
 int SSI_STCCR_PSR ; 
 int readl (scalar_t__) ; 
 struct imx_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_set_dai_clkdiv(struct snd_soc_dai *cpu_dai,
				  int div_id, int div)
{
	struct imx_ssi *ssi = snd_soc_dai_get_drvdata(cpu_dai);
	u32 stccr, srccr;

	stccr = readl(ssi->base + SSI_STCCR);
	srccr = readl(ssi->base + SSI_SRCCR);

	switch (div_id) {
	case IMX_SSI_TX_DIV_2:
		stccr &= ~SSI_STCCR_DIV2;
		stccr |= div;
		break;
	case IMX_SSI_TX_DIV_PSR:
		stccr &= ~SSI_STCCR_PSR;
		stccr |= div;
		break;
	case IMX_SSI_TX_DIV_PM:
		stccr &= ~0xff;
		stccr |= SSI_STCCR_PM(div);
		break;
	case IMX_SSI_RX_DIV_2:
		stccr &= ~SSI_STCCR_DIV2;
		stccr |= div;
		break;
	case IMX_SSI_RX_DIV_PSR:
		stccr &= ~SSI_STCCR_PSR;
		stccr |= div;
		break;
	case IMX_SSI_RX_DIV_PM:
		stccr &= ~0xff;
		stccr |= SSI_STCCR_PM(div);
		break;
	default:
		return -EINVAL;
	}

	writel(stccr, ssi->base + SSI_STCCR);
	writel(srccr, ssi->base + SSI_SRCCR);

	return 0;
}