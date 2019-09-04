#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {unsigned int pll_in; unsigned int pll_out; int regvalue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5632_DAI_CONTROL ; 
 int ALC5632_DAI_SDP_SLAVE_MODE ; 
 int /*<<< orphan*/  ALC5632_GPCR1 ; 
 int /*<<< orphan*/  ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1 ; 
 int /*<<< orphan*/  ALC5632_GPCR2 ; 
 int /*<<< orphan*/  ALC5632_PLL1_CTRL ; 
#define  ALC5632_PLL_FR_BCLK 130 
#define  ALC5632_PLL_FR_MCLK 129 
#define  ALC5632_PLL_FR_VBCLK 128 
 int /*<<< orphan*/  ALC5632_PWR_ADD2_PLL1 ; 
 int /*<<< orphan*/  ALC5632_PWR_ADD2_PLL2 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD2 ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* codec_master_pll_div ; 
 TYPE_1__* codec_slave_pll_div ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alc5632_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
		int source, unsigned int freq_in, unsigned int freq_out)
{
	int i;
	struct snd_soc_component *component = codec_dai->component;
	int gbl_clk = 0, pll_div = 0;
	u16 reg;

	if (pll_id < ALC5632_PLL_FR_MCLK || pll_id > ALC5632_PLL_FR_VBCLK)
		return -EINVAL;

	/* Disable PLL power */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL1,
				0);
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL2,
				0);

	/* pll is not used in slave mode */
	reg = snd_soc_component_read32(component, ALC5632_DAI_CONTROL);
	if (reg & ALC5632_DAI_SDP_SLAVE_MODE)
		return 0;

	if (!freq_in || !freq_out)
		return 0;

	switch (pll_id) {
	case ALC5632_PLL_FR_MCLK:
		for (i = 0; i < ARRAY_SIZE(codec_master_pll_div); i++) {
			if (codec_master_pll_div[i].pll_in == freq_in
			   && codec_master_pll_div[i].pll_out == freq_out) {
				/* PLL source from MCLK */
				pll_div  = codec_master_pll_div[i].regvalue;
				break;
			}
		}
		break;
	case ALC5632_PLL_FR_BCLK:
		for (i = 0; i < ARRAY_SIZE(codec_slave_pll_div); i++) {
			if (codec_slave_pll_div[i].pll_in == freq_in
			   && codec_slave_pll_div[i].pll_out == freq_out) {
				/* PLL source from Bitclk */
				gbl_clk = ALC5632_PLL_FR_BCLK;
				pll_div = codec_slave_pll_div[i].regvalue;
				break;
			}
		}
		break;
	case ALC5632_PLL_FR_VBCLK:
		for (i = 0; i < ARRAY_SIZE(codec_slave_pll_div); i++) {
			if (codec_slave_pll_div[i].pll_in == freq_in
			   && codec_slave_pll_div[i].pll_out == freq_out) {
				/* PLL source from voice clock */
				gbl_clk = ALC5632_PLL_FR_VBCLK;
				pll_div = codec_slave_pll_div[i].regvalue;
				break;
			}
		}
		break;
	default:
		return -EINVAL;
	}

	if (!pll_div)
		return -EINVAL;

	/* choose MCLK/BCLK/VBCLK */
	snd_soc_component_write(component, ALC5632_GPCR2, gbl_clk);
	/* choose PLL1 clock rate */
	snd_soc_component_write(component, ALC5632_PLL1_CTRL, pll_div);
	/* enable PLL1 */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL1,
				ALC5632_PWR_ADD2_PLL1);
	/* enable PLL2 */
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_ADD2_PLL2,
				ALC5632_PWR_ADD2_PLL2);
	/* use PLL1 as main SYSCLK */
	snd_soc_component_update_bits(component, ALC5632_GPCR1,
			ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1,
			ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1);

	return 0;
}