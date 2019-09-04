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
typedef  unsigned int u32 ;
struct snd_soc_dai {int dummy; } ;
struct imx_ssi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SSI_SRCCR ; 
 scalar_t__ SSI_SRMSK ; 
 scalar_t__ SSI_STCCR ; 
 unsigned int SSI_STCCR_DC (int) ; 
 unsigned int SSI_STCCR_DC_MASK ; 
 scalar_t__ SSI_STMSK ; 
 unsigned int readl (scalar_t__) ; 
 struct imx_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_set_dai_tdm_slot(struct snd_soc_dai *cpu_dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct imx_ssi *ssi = snd_soc_dai_get_drvdata(cpu_dai);
	u32 sccr;

	sccr = readl(ssi->base + SSI_STCCR);
	sccr &= ~SSI_STCCR_DC_MASK;
	sccr |= SSI_STCCR_DC(slots - 1);
	writel(sccr, ssi->base + SSI_STCCR);

	sccr = readl(ssi->base + SSI_SRCCR);
	sccr &= ~SSI_STCCR_DC_MASK;
	sccr |= SSI_STCCR_DC(slots - 1);
	writel(sccr, ssi->base + SSI_SRCCR);

	writel(~tx_mask, ssi->base + SSI_STMSK);
	writel(~rx_mask, ssi->base + SSI_SRMSK);

	return 0;
}