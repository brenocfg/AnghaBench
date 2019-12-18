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
struct regmap {int dummy; } ;
struct nau8540 {struct regmap* regmap; } ;

/* Variables and functions */
 int NAU8540_ADC_OSR_64 ; 
 int NAU8540_ADC_OSR_MASK ; 
 int NAU8540_CH_SYNC ; 
 int NAU8540_CLK_ADC_EN ; 
 int NAU8540_CLK_I2S_EN ; 
 int NAU8540_FEPGA1_MODCH1_SHT ; 
 int NAU8540_FEPGA1_MODCH2_SHT ; 
 int NAU8540_FEPGA2_MODCH3_SHT ; 
 int NAU8540_FEPGA2_MODCH4_SHT ; 
 int NAU8540_GLOBAL_BIAS_EN ; 
 int NAU8540_I2S_DO12_TRI ; 
 int NAU8540_I2S_DO34_TRI ; 
 int NAU8540_PRECHARGE_DIS ; 
 int NAU8540_PU_PRE ; 
 int /*<<< orphan*/  NAU8540_REG_ADC_SAMPLE_RATE ; 
 int /*<<< orphan*/  NAU8540_REG_CLOCK_CTRL ; 
 int /*<<< orphan*/  NAU8540_REG_FEPGA1 ; 
 int /*<<< orphan*/  NAU8540_REG_FEPGA2 ; 
 int /*<<< orphan*/  NAU8540_REG_MIC_BIAS ; 
 int /*<<< orphan*/  NAU8540_REG_PCM_CTRL1 ; 
 int /*<<< orphan*/  NAU8540_REG_PCM_CTRL2 ; 
 int /*<<< orphan*/  NAU8540_REG_REFERENCE ; 
 int /*<<< orphan*/  NAU8540_REG_VMID_CTRL ; 
 int NAU8540_VMID_EN ; 
 int NAU8540_VMID_SEL_MASK ; 
 int NAU8540_VMID_SEL_SFT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8540_init_regs(struct nau8540 *nau8540)
{
	struct regmap *regmap = nau8540->regmap;

	/* Enable Bias/VMID/VMID Tieoff */
	regmap_update_bits(regmap, NAU8540_REG_VMID_CTRL,
		NAU8540_VMID_EN | NAU8540_VMID_SEL_MASK,
		NAU8540_VMID_EN | (0x2 << NAU8540_VMID_SEL_SFT));
	regmap_update_bits(regmap, NAU8540_REG_REFERENCE,
		NAU8540_PRECHARGE_DIS | NAU8540_GLOBAL_BIAS_EN,
		NAU8540_PRECHARGE_DIS | NAU8540_GLOBAL_BIAS_EN);
	mdelay(2);
	regmap_update_bits(regmap, NAU8540_REG_MIC_BIAS,
		NAU8540_PU_PRE, NAU8540_PU_PRE);
	regmap_update_bits(regmap, NAU8540_REG_CLOCK_CTRL,
		NAU8540_CLK_ADC_EN | NAU8540_CLK_I2S_EN,
		NAU8540_CLK_ADC_EN | NAU8540_CLK_I2S_EN);
	/* ADC OSR selection, CLK_ADC = Fs * OSR;
	 * Channel time alignment enable.
	 */
	regmap_update_bits(regmap, NAU8540_REG_ADC_SAMPLE_RATE,
		NAU8540_CH_SYNC | NAU8540_ADC_OSR_MASK,
		NAU8540_CH_SYNC | NAU8540_ADC_OSR_64);
	/* PGA input mode selection */
	regmap_update_bits(regmap, NAU8540_REG_FEPGA1,
		NAU8540_FEPGA1_MODCH2_SHT | NAU8540_FEPGA1_MODCH1_SHT,
		NAU8540_FEPGA1_MODCH2_SHT | NAU8540_FEPGA1_MODCH1_SHT);
	regmap_update_bits(regmap, NAU8540_REG_FEPGA2,
		NAU8540_FEPGA2_MODCH4_SHT | NAU8540_FEPGA2_MODCH3_SHT,
		NAU8540_FEPGA2_MODCH4_SHT | NAU8540_FEPGA2_MODCH3_SHT);
	/* DO12 and DO34 pad output disable */
	regmap_update_bits(regmap, NAU8540_REG_PCM_CTRL1,
		NAU8540_I2S_DO12_TRI, NAU8540_I2S_DO12_TRI);
	regmap_update_bits(regmap, NAU8540_REG_PCM_CTRL2,
		NAU8540_I2S_DO34_TRI, NAU8540_I2S_DO34_TRI);
}