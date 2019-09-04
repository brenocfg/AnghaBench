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
struct TYPE_3__ {int /*<<< orphan*/ * status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rpi_cirrus_priv {int /*<<< orphan*/ * iec958_status; } ;

/* Variables and functions */
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_spdif_playback_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	int i;

	for (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] = priv->iec958_status[i];

	return 0;
}