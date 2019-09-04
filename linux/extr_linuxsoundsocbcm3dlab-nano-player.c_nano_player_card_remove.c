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
struct snd_soc_card {int dummy; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NANO_CFG ; 
 int /*<<< orphan*/  NANO_CFG_OFF ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int nano_player_card_remove(struct snd_soc_card *card)
{
	/* disable internal audio bus */
	struct regmap *regmap = snd_soc_card_get_drvdata(card);

	return regmap_write(regmap, NANO_CFG, NANO_CFG_OFF);
}