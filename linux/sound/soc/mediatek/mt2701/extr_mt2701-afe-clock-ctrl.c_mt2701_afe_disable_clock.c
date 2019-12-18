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
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_DAC_CON0 ; 
 int /*<<< orphan*/  AFE_DAC_CON0_AFE_ON ; 
 int /*<<< orphan*/  ASYS_TOP_CON ; 
 int /*<<< orphan*/  ASYS_TOP_CON_ASYS_TIMING_ON ; 
 int /*<<< orphan*/  mt2701_afe_disable_audsys (struct mtk_base_afe*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt2701_afe_disable_clock(struct mtk_base_afe *afe)
{
	regmap_update_bits(afe->regmap, ASYS_TOP_CON,
			   ASYS_TOP_CON_ASYS_TIMING_ON, 0);
	regmap_update_bits(afe->regmap, AFE_DAC_CON0,
			   AFE_DAC_CON0_AFE_ON, 0);

	mt2701_afe_disable_audsys(afe);

	return 0;
}