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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ private; } ;
struct soc_enum {TYPE_1__ dobj; } ;
struct snd_soc_dapm_widget {struct skl_module_cfg* priv; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct skl_module_cfg {scalar_t__ dmic_ch_type; int /*<<< orphan*/  dmic_ch_combo_index; } ;

/* Variables and functions */
 struct snd_soc_dapm_widget* snd_soc_dapm_kcontrol_widget (struct snd_kcontrol*) ; 

__attribute__((used)) static int skl_tplg_mic_control_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	struct skl_module_cfg *mconfig = w->priv;
	struct soc_enum *ec = (struct soc_enum *)kcontrol->private_value;
	u32 ch_type = *((u32 *)ec->dobj.private);

	if (mconfig->dmic_ch_type == ch_type)
		ucontrol->value.enumerated.item[0] =
					mconfig->dmic_ch_combo_index;
	else
		ucontrol->value.enumerated.item[0] = 0;

	return 0;
}