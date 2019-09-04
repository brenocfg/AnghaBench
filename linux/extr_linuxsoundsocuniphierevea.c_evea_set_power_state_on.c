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
struct evea_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AANAPOW ; 
 int /*<<< orphan*/  AANAPOW_A_POWD ; 
 int /*<<< orphan*/  ADAC1ODC ; 
 int /*<<< orphan*/  ADAC1ODC_ADAC_RAMPCLT_MASK ; 
 int /*<<< orphan*/  ADAC1ODC_ADAC_RAMPCLT_REDUCE ; 
 int /*<<< orphan*/  ADAC1ODC_HP_DIS_RES_MASK ; 
 int /*<<< orphan*/  ADAC1ODC_HP_DIS_RES_ON ; 
 int /*<<< orphan*/  ADACSEQ2 (int) ; 
 int /*<<< orphan*/  ADACSEQ2_ADACIN_FIX ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evea_set_power_state_on(struct evea_priv *evea)
{
	struct regmap *map = evea->regmap;

	regmap_update_bits(map, AANAPOW, AANAPOW_A_POWD,
			   AANAPOW_A_POWD);

	regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
			   ADAC1ODC_HP_DIS_RES_ON);

	regmap_update_bits(map, ADAC1ODC, ADAC1ODC_ADAC_RAMPCLT_MASK,
			   ADAC1ODC_ADAC_RAMPCLT_REDUCE);

	regmap_update_bits(map, ADACSEQ2(0), ADACSEQ2_ADACIN_FIX, 0);
	regmap_update_bits(map, ADACSEQ2(1), ADACSEQ2_ADACIN_FIX, 0);
	regmap_update_bits(map, ADACSEQ2(2), ADACSEQ2_ADACIN_FIX, 0);
}