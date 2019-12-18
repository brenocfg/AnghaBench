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
struct mtk_base_afe {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_DAC_CON0 ; 
 int /*<<< orphan*/  AFE_DAC_CON0_AFE_ON ; 
 int /*<<< orphan*/  ASYS_TOP_CON ; 
 int /*<<< orphan*/  ASYS_TOP_CON_ASYS_TIMING_ON ; 
 int /*<<< orphan*/  PWR1_ASM_CON1 ; 
 int /*<<< orphan*/  PWR1_ASM_CON1_INIT_VAL ; 
 int /*<<< orphan*/  PWR2_ASM_CON1 ; 
 int /*<<< orphan*/  PWR2_ASM_CON1_INIT_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mt2701_afe_enable_audsys (struct mtk_base_afe*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt2701_afe_enable_clock(struct mtk_base_afe *afe)
{
	int ret;

	/* Enable audio system */
	ret = mt2701_afe_enable_audsys(afe);
	if (ret) {
		dev_err(afe->dev, "failed to enable audio system %d\n", ret);
		return ret;
	}

	regmap_update_bits(afe->regmap, ASYS_TOP_CON,
			   ASYS_TOP_CON_ASYS_TIMING_ON,
			   ASYS_TOP_CON_ASYS_TIMING_ON);
	regmap_update_bits(afe->regmap, AFE_DAC_CON0,
			   AFE_DAC_CON0_AFE_ON,
			   AFE_DAC_CON0_AFE_ON);

	/* Configure ASRC */
	regmap_write(afe->regmap, PWR1_ASM_CON1, PWR1_ASM_CON1_INIT_VAL);
	regmap_write(afe->regmap, PWR2_ASM_CON1, PWR2_ASM_CON1_INIT_VAL);

	return 0;
}