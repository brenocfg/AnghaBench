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
struct aic31xx_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void aic31xx_power_off(struct snd_soc_component *component)
{
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	regcache_cache_only(aic31xx->regmap, true);
	regulator_bulk_disable(ARRAY_SIZE(aic31xx->supplies),
			       aic31xx->supplies);
}