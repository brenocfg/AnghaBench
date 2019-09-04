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
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NANO_CFG ; 
 int NANO_CFG_BLINK ; 
 int NANO_CFG_ENA ; 
 int /*<<< orphan*/  NANO_ID ; 
 unsigned int NANO_ID_VAL ; 
 int /*<<< orphan*/  NANO_VER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct regmap* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int nano_player_card_probe(struct snd_soc_card *card)
{
	struct regmap *regmap = snd_soc_card_get_drvdata(card);
	unsigned int val;

	/* check hardware integrity */
	regmap_read(regmap, NANO_ID, &val);
	if (val != NANO_ID_VAL) {
		dev_err(card->dev, "Invalid ID register 0x%02X\n", val);
		return -ENODEV;
	}

	/* report version to the user */
	regmap_read(regmap, NANO_VER, &val);
	dev_notice(card->dev, "Started 3Dlab Nano Player driver (v%d)\n", val);

	/* enable internal audio bus and blink status LED */
	return regmap_write(regmap, NANO_CFG, NANO_CFG_ENA | NANO_CFG_BLINK);
}