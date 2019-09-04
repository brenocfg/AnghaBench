#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct mt2701_cs42448_private {int /*<<< orphan*/  i2s1_in_mux; } ;

/* Variables and functions */
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct mt2701_cs42448_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int mt2701_cs42448_i2sin1_mux_get(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct mt2701_cs42448_private *priv = snd_soc_card_get_drvdata(card);

	ucontrol->value.integer.value[0] = priv->i2s1_in_mux;
	return 0;
}