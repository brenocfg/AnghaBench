#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {unsigned int private_value; TYPE_1__ id; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int NANO_CTRL2_VAL ; 
 int /*<<< orphan*/  NANO_DAC_CTRL2 ; 
 int /*<<< orphan*/  NANO_DAC_LATT ; 
 int /*<<< orphan*/  NANO_DAC_RATT ; 
 int /*<<< orphan*/  nano_player_spi_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct regmap* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nano_player_ctrl_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	/* program control value to hardware */
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct regmap *regmap = snd_soc_card_get_drvdata(card);

	if (strstr(kcontrol->id.name, "Volume")) {
		unsigned int vol = ucontrol->value.integer.value[0];
		unsigned int att = 255 - (2 * (100 - vol));

		nano_player_spi_write(regmap, NANO_DAC_LATT, att);
		nano_player_spi_write(regmap, NANO_DAC_RATT, att);
		kcontrol->private_value = vol;
	} else {
		unsigned int mute = ucontrol->value.integer.value[0];
		unsigned int reg = NANO_CTRL2_VAL | mute;

		nano_player_spi_write(regmap, NANO_DAC_CTRL2, reg);
		kcontrol->private_value = mute;
	}
	return 0;
}