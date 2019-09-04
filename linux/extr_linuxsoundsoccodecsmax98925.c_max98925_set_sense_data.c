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
struct max98925_priv {int v_slot; int i_slot; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int M98925_DAI_IMON_EN_MASK ; 
 int M98925_DAI_IMON_SLOT_MASK ; 
 int M98925_DAI_IMON_SLOT_SHIFT ; 
 int M98925_DAI_VMON_EN_MASK ; 
 int M98925_DAI_VMON_SLOT_MASK ; 
 int M98925_DAI_VMON_SLOT_SHIFT ; 
 int /*<<< orphan*/  MAX98925_DOUT_CFG_IMON ; 
 int /*<<< orphan*/  MAX98925_DOUT_CFG_VMON ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void max98925_set_sense_data(struct max98925_priv *max98925)
{
	/* set VMON slots */
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_VMON,
		M98925_DAI_VMON_EN_MASK, M98925_DAI_VMON_EN_MASK);
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_VMON,
		M98925_DAI_VMON_SLOT_MASK,
		max98925->v_slot << M98925_DAI_VMON_SLOT_SHIFT);
	/* set IMON slots */
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_IMON,
		M98925_DAI_IMON_EN_MASK, M98925_DAI_IMON_EN_MASK);
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_IMON,
		M98925_DAI_IMON_SLOT_MASK,
		max98925->i_slot << M98925_DAI_IMON_SLOT_SHIFT);
}