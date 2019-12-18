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
struct evea_priv {scalar_t__ switch_hp; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAC1ODC ; 
 int /*<<< orphan*/  ADAC1ODC_HP_DIS_RES_MASK ; 
 int /*<<< orphan*/  ADAC1ODC_HP_DIS_RES_OFF ; 
 int /*<<< orphan*/  ADAC1ODC_HP_DIS_RES_ON ; 
 int /*<<< orphan*/  ADACSEQ1 (int) ; 
 int /*<<< orphan*/  ADACSEQ1_MMUTE ; 
 int /*<<< orphan*/  AHPOUTPOW ; 
 int /*<<< orphan*/  AHPOUTPOW_HP_ON ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evea_update_switch_hp(struct evea_priv *evea)
{
	struct regmap *map = evea->regmap;

	if (evea->switch_hp) {
		regmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE, 0);

		regmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON,
				   AHPOUTPOW_HP_ON);

		regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
				   ADAC1ODC_HP_DIS_RES_OFF);
	} else {
		regmap_update_bits(map, ADAC1ODC, ADAC1ODC_HP_DIS_RES_MASK,
				   ADAC1ODC_HP_DIS_RES_ON);

		regmap_update_bits(map, ADACSEQ1(1), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		regmap_update_bits(map, AHPOUTPOW, AHPOUTPOW_HP_ON, 0);
	}

	return 0;
}