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
struct TYPE_4__ {int /*<<< orphan*/  mute; } ;
struct spdif_out_dev {TYPE_1__ saved_params; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct spdif_out_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spdif_digital_mute (struct snd_soc_dai*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spdif_mute_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct spdif_out_dev *host = snd_soc_dai_get_drvdata(cpu_dai);

	if (host->saved_params.mute == ucontrol->value.integer.value[0])
		return 0;

	spdif_digital_mute(cpu_dai, ucontrol->value.integer.value[0]);

	return 1;
}