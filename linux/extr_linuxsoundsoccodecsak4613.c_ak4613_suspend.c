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
struct regmap {int dummy; } ;

/* Variables and functions */
 struct regmap* dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cache_only (struct regmap*,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (struct regmap*) ; 

__attribute__((used)) static int ak4613_suspend(struct snd_soc_component *component)
{
	struct regmap *regmap = dev_get_regmap(component->dev, NULL);

	regcache_cache_only(regmap, true);
	regcache_mark_dirty(regmap);
	return 0;
}