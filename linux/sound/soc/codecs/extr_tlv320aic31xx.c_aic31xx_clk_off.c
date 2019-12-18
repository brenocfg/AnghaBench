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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC31XX_BCLKN ; 
 int /*<<< orphan*/  AIC31XX_MADC ; 
 int /*<<< orphan*/  AIC31XX_MDAC ; 
 int /*<<< orphan*/  AIC31XX_NADC ; 
 int /*<<< orphan*/  AIC31XX_NDAC ; 
 int /*<<< orphan*/  AIC31XX_PLLPR ; 
 int /*<<< orphan*/  AIC31XX_PM_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aic31xx_clk_off(struct snd_soc_component *component)
{
	u8 mask = AIC31XX_PM_MASK;
	u8 off = 0;

	dev_dbg(component->dev, "codec clock -> off\n");
	snd_soc_component_update_bits(component, AIC31XX_BCLKN, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_PLLPR, mask, off);
}