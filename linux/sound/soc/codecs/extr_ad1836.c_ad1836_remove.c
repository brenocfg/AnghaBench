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
struct ad1836_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1836_ADC_CTRL2 ; 
 int /*<<< orphan*/  AD1836_ADC_SERFMT_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad1836_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void ad1836_remove(struct snd_soc_component *component)
{
	struct ad1836_priv *ad1836 = snd_soc_component_get_drvdata(component);
	/* reset clock control mode */
	regmap_update_bits(ad1836->regmap, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, 0);
}