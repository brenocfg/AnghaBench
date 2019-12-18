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
struct evea_priv {scalar_t__ switch_lo; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADACSEQ1 (int) ; 
 int ADACSEQ1_MMUTE ; 
 int /*<<< orphan*/  ALO1OUTPOW ; 
 int ALO1OUTPOW_LO1_ON ; 
 int /*<<< orphan*/  ALO2OUTPOW ; 
 int ALO2OUTPOW_ADAC2_MUTE ; 
 int ALO2OUTPOW_LO2_ON ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int evea_update_switch_lo(struct evea_priv *evea)
{
	struct regmap *map = evea->regmap;

	if (evea->switch_lo) {
		regmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE, 0);
		regmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE, 0);

		regmap_update_bits(map, ALO1OUTPOW, ALO1OUTPOW_LO1_ON,
				   ALO1OUTPOW_LO1_ON);
		regmap_update_bits(map, ALO2OUTPOW,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON);
	} else {
		regmap_update_bits(map, ADACSEQ1(0), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);
		regmap_update_bits(map, ADACSEQ1(2), ADACSEQ1_MMUTE,
				   ADACSEQ1_MMUTE);

		regmap_update_bits(map, ALO1OUTPOW, ALO1OUTPOW_LO1_ON, 0);
		regmap_update_bits(map, ALO2OUTPOW,
				   ALO2OUTPOW_ADAC2_MUTE | ALO2OUTPOW_LO2_ON,
				   0);
	}

	return 0;
}