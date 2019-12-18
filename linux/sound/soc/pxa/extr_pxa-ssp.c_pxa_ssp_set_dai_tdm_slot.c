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
struct ssp_priv {struct ssp_device* ssp; } ;
struct ssp_device {int dummy; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 unsigned int SSCR0_DSS ; 
 unsigned int SSCR0_DataSize (int) ; 
 unsigned int SSCR0_EDSS ; 
 unsigned int SSCR0_MOD ; 
 unsigned int SSCR0_SlotsPerFrm (int) ; 
 int /*<<< orphan*/  SSRSA ; 
 int /*<<< orphan*/  SSTSA ; 
 unsigned int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ssp_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int pxa_ssp_set_dai_tdm_slot(struct snd_soc_dai *cpu_dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct ssp_device *ssp = priv->ssp;
	u32 sscr0;

	sscr0 = pxa_ssp_read_reg(ssp, SSCR0);
	sscr0 &= ~(SSCR0_MOD | SSCR0_SlotsPerFrm(8) | SSCR0_EDSS | SSCR0_DSS);

	/* set slot width */
	if (slot_width > 16)
		sscr0 |= SSCR0_EDSS | SSCR0_DataSize(slot_width - 16);
	else
		sscr0 |= SSCR0_DataSize(slot_width);

	if (slots > 1) {
		/* enable network mode */
		sscr0 |= SSCR0_MOD;

		/* set number of active slots */
		sscr0 |= SSCR0_SlotsPerFrm(slots);

		/* set active slot mask */
		pxa_ssp_write_reg(ssp, SSTSA, tx_mask);
		pxa_ssp_write_reg(ssp, SSRSA, rx_mask);
	}
	pxa_ssp_write_reg(ssp, SSCR0, sscr0);

	return 0;
}