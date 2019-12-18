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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct mxs_saif {scalar_t__ id; scalar_t__ master_id; scalar_t__ base; } ;

/* Variables and functions */
 int BM_SAIF_CTRL_BITCLK_EDGE ; 
 int BM_SAIF_CTRL_CLKGATE ; 
 int BM_SAIF_CTRL_DELAY ; 
 int BM_SAIF_CTRL_JUSTIFY ; 
 int BM_SAIF_CTRL_LRCLK_POLARITY ; 
 int BM_SAIF_CTRL_SFTRST ; 
 int BM_SAIF_CTRL_SLAVE_MODE ; 
 int BM_SAIF_STAT_BUSY ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MXS_CLR_ADDR ; 
 scalar_t__ SAIF_CTRL ; 
 scalar_t__ SAIF_STAT ; 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mxs_saif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mxs_saif_set_dai_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	u32 scr, stat;
	u32 scr0;
	struct mxs_saif *saif = snd_soc_dai_get_drvdata(cpu_dai);

	stat = __raw_readl(saif->base + SAIF_STAT);
	if (stat & BM_SAIF_STAT_BUSY) {
		dev_err(cpu_dai->dev, "error: busy\n");
		return -EBUSY;
	}

	/* If SAIF1 is configured as slave, the clk gate needs to be cleared
	 * before the register can be written.
	 */
	if (saif->id != saif->master_id) {
		__raw_writel(BM_SAIF_CTRL_SFTRST,
			saif->base + SAIF_CTRL + MXS_CLR_ADDR);
		__raw_writel(BM_SAIF_CTRL_CLKGATE,
			saif->base + SAIF_CTRL + MXS_CLR_ADDR);
	}

	scr0 = __raw_readl(saif->base + SAIF_CTRL);
	scr0 = scr0 & ~BM_SAIF_CTRL_BITCLK_EDGE & ~BM_SAIF_CTRL_LRCLK_POLARITY \
		& ~BM_SAIF_CTRL_JUSTIFY & ~BM_SAIF_CTRL_DELAY;
	scr = 0;

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* data frame low 1clk before data */
		scr |= BM_SAIF_CTRL_DELAY;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		/* data frame high with data */
		scr &= ~BM_SAIF_CTRL_DELAY;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		scr &= ~BM_SAIF_CTRL_JUSTIFY;
		break;
	default:
		return -EINVAL;
	}

	/* DAI clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		scr |= BM_SAIF_CTRL_BITCLK_EDGE;
		scr |= BM_SAIF_CTRL_LRCLK_POLARITY;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		scr |= BM_SAIF_CTRL_BITCLK_EDGE;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		scr &= ~BM_SAIF_CTRL_BITCLK_EDGE;
		scr |= BM_SAIF_CTRL_LRCLK_POLARITY;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		scr &= ~BM_SAIF_CTRL_BITCLK_EDGE;
		scr &= ~BM_SAIF_CTRL_LRCLK_POLARITY;
		break;
	}

	/*
	 * Note: We simply just support master mode since SAIF TX can only
	 * work as master.
	 * Here the master is relative to codec side.
	 * Saif internally could be slave when working on EXTMASTER mode.
	 * We just hide this to machine driver.
	 */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		if (saif->id == saif->master_id)
			scr &= ~BM_SAIF_CTRL_SLAVE_MODE;
		else
			scr |= BM_SAIF_CTRL_SLAVE_MODE;

		__raw_writel(scr | scr0, saif->base + SAIF_CTRL);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}