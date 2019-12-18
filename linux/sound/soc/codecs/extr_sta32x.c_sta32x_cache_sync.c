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
struct sta32x_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STA32X_MMUTE ; 
 unsigned int STA32X_MMUTE_MMUTE ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta32x_sync_coef_shadow (struct snd_soc_component*) ; 

__attribute__((used)) static int sta32x_cache_sync(struct snd_soc_component *component)
{
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	unsigned int mute;
	int rc;

	/* mute during register sync */
	regmap_read(sta32x->regmap, STA32X_MMUTE, &mute);
	regmap_write(sta32x->regmap, STA32X_MMUTE, mute | STA32X_MMUTE_MMUTE);
	sta32x_sync_coef_shadow(component);
	rc = regcache_sync(sta32x->regmap);
	regmap_write(sta32x->regmap, STA32X_MMUTE, mute);
	return rc;
}