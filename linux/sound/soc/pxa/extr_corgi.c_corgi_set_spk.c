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
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  corgi_ext_control (int /*<<< orphan*/ *) ; 
 scalar_t__ corgi_spk_func ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int corgi_set_spk(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	if (corgi_spk_func == ucontrol->value.enumerated.item[0])
		return 0;

	corgi_spk_func = ucontrol->value.enumerated.item[0];
	corgi_ext_control(&card->dapm);
	return 1;
}