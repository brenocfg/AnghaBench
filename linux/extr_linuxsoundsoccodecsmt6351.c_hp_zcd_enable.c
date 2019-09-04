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
struct snd_soc_component {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6351_ZCD_CON0 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hp_zcd_enable(struct snd_soc_component *cmpnt)
{
	/* Enable ZCD, for minimize pop noise */
	/* when adjust gain during HP buffer on */
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x7 << 8, 0x1 << 8);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 7, 0x0 << 7);

	/* timeout, 1=5ms, 0=30ms */
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 6, 0x1 << 6);

	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x3 << 4, 0x0 << 4);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x7 << 1, 0x5 << 1);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 0, 0x1 << 0);
}