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
struct max98926_priv {int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98926_DOUT_HIZ_CFG4 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98926_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98926_probe(struct snd_soc_component *component)
{
	struct max98926_priv *max98926 = snd_soc_component_get_drvdata(component);

	max98926->component = component;

	/* Hi-Z all the slots */
	regmap_write(max98926->regmap, MAX98926_DOUT_HIZ_CFG4, 0xF0);
	return 0;
}