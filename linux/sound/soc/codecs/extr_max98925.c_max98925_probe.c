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
struct snd_soc_component {int dummy; } ;
struct max98925_priv {int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;

/* Variables and functions */
 int M98925_DAI_DLY_MASK ; 
 int /*<<< orphan*/  MAX98925_ALC_CONFIGURATION ; 
 int /*<<< orphan*/  MAX98925_BOOST_LIMITER ; 
 int /*<<< orphan*/  MAX98925_CONFIGURATION ; 
 int /*<<< orphan*/  MAX98925_DOUT_HIZ_CFG1 ; 
 int /*<<< orphan*/  MAX98925_DOUT_HIZ_CFG2 ; 
 int /*<<< orphan*/  MAX98925_DOUT_HIZ_CFG3 ; 
 int /*<<< orphan*/  MAX98925_DOUT_HIZ_CFG4 ; 
 int /*<<< orphan*/  MAX98925_FILTERS ; 
 int /*<<< orphan*/  MAX98925_FORMAT ; 
 int /*<<< orphan*/  MAX98925_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  MAX98925_TDM_SLOT_SELECT ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98925_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98925_probe(struct snd_soc_component *component)
{
	struct max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	max98925->component = component;
	regmap_write(max98925->regmap, MAX98925_GLOBAL_ENABLE, 0x00);
	/* It's not the default but we need to set DAI_DLY */
	regmap_write(max98925->regmap,
			MAX98925_FORMAT, M98925_DAI_DLY_MASK);
	regmap_write(max98925->regmap, MAX98925_TDM_SLOT_SELECT, 0xC8);
	regmap_write(max98925->regmap, MAX98925_DOUT_HIZ_CFG1, 0xFF);
	regmap_write(max98925->regmap, MAX98925_DOUT_HIZ_CFG2, 0xFF);
	regmap_write(max98925->regmap, MAX98925_DOUT_HIZ_CFG3, 0xFF);
	regmap_write(max98925->regmap, MAX98925_DOUT_HIZ_CFG4, 0xF0);
	regmap_write(max98925->regmap, MAX98925_FILTERS, 0xD8);
	regmap_write(max98925->regmap, MAX98925_ALC_CONFIGURATION, 0xF8);
	regmap_write(max98925->regmap, MAX98925_CONFIGURATION, 0xF0);
	/* Disable ALC muting */
	regmap_write(max98925->regmap, MAX98925_BOOST_LIMITER, 0xF8);
	return 0;
}