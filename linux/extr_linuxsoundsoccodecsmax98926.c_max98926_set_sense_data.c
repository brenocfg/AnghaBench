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
struct max98926_priv {int /*<<< orphan*/  v_slot; int /*<<< orphan*/  regmap; int /*<<< orphan*/  i_slot; int /*<<< orphan*/  interleave_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98926_DAI_IMON_EN_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_IMON_SLOT_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_INTERLEAVE_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_INTERLEAVE_SLOT_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_VMON_EN_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_VMON_SLOT_MASK ; 
 int /*<<< orphan*/  MAX98926_DOUT_CFG_IMON ; 
 int /*<<< orphan*/  MAX98926_DOUT_CFG_VBAT ; 
 int /*<<< orphan*/  MAX98926_DOUT_CFG_VMON ; 
 int /*<<< orphan*/  MAX98926_FORMAT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max98926_set_sense_data(struct max98926_priv *max98926)
{
	regmap_update_bits(max98926->regmap,
		MAX98926_DOUT_CFG_VMON,
		MAX98926_DAI_VMON_EN_MASK,
		MAX98926_DAI_VMON_EN_MASK);
	regmap_update_bits(max98926->regmap,
		MAX98926_DOUT_CFG_IMON,
		MAX98926_DAI_IMON_EN_MASK,
		MAX98926_DAI_IMON_EN_MASK);

	if (!max98926->interleave_mode) {
		/* set VMON slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_VMON,
			MAX98926_DAI_VMON_SLOT_MASK,
			max98926->v_slot);
		/* set IMON slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_IMON,
			MAX98926_DAI_IMON_SLOT_MASK,
			max98926->i_slot);
	} else {
		/* enable interleave mode */
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_INTERLEAVE_MASK,
			MAX98926_DAI_INTERLEAVE_MASK);
		/* set interleave slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_VBAT,
			MAX98926_DAI_INTERLEAVE_SLOT_MASK,
			max98926->v_slot);
	}
}