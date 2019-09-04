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
struct TYPE_4__ {scalar_t__* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct rpi_cirrus_priv {scalar_t__ min_rate_idx; } ;

/* Variables and functions */
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_min_rate_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	int changed = 0;

	if (priv->min_rate_idx != ucontrol->value.enumerated.item[0]) {
		changed = 1;
		priv->min_rate_idx = ucontrol->value.enumerated.item[0];
	}

	return changed;
}