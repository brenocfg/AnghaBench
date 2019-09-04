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
struct sta350_priv {int* coef_shadow; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STA350_B1CF1 ; 
 int /*<<< orphan*/  STA350_B1CF2 ; 
 int /*<<< orphan*/  STA350_B1CF3 ; 
 int /*<<< orphan*/  STA350_CFADDR2 ; 
 int /*<<< orphan*/  STA350_CFUD ; 
 int STA350_COEF_COUNT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct sta350_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int sta350_sync_coef_shadow(struct snd_soc_component *component)
{
	struct sta350_priv *sta350 = snd_soc_component_get_drvdata(component);
	unsigned int cfud;
	int i;

	/* preserve reserved bits in STA350_CFUD */
	regmap_read(sta350->regmap, STA350_CFUD, &cfud);
	cfud &= 0xf0;

	for (i = 0; i < STA350_COEF_COUNT; i++) {
		regmap_write(sta350->regmap, STA350_CFADDR2, i);
		regmap_write(sta350->regmap, STA350_B1CF1,
			     (sta350->coef_shadow[i] >> 16) & 0xff);
		regmap_write(sta350->regmap, STA350_B1CF2,
			     (sta350->coef_shadow[i] >> 8) & 0xff);
		regmap_write(sta350->regmap, STA350_B1CF3,
			     (sta350->coef_shadow[i]) & 0xff);
		/*
		 * chip documentation does not say if the bits are
		 * self-clearing, so do it explicitly
		 */
		regmap_write(sta350->regmap, STA350_CFUD, cfud);
		regmap_write(sta350->regmap, STA350_CFUD, cfud | 0x01);
	}
	return 0;
}