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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct alc5623_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 struct alc5623_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int alc5623_resume(struct snd_soc_component *component)
{
	struct alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	int ret;

	/* Sync reg_cache with the hardware */
	regcache_cache_only(alc5623->regmap, false);
	ret = regcache_sync(alc5623->regmap);
	if (ret != 0) {
		dev_err(component->dev, "Failed to sync register cache: %d\n",
			ret);
		regcache_cache_only(alc5623->regmap, true);
		return ret;
	}

	return 0;
}