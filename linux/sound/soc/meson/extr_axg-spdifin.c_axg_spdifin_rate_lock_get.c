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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct axg_spdifin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axg_spdifin_get_rate (struct axg_spdifin*) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct axg_spdifin* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int axg_spdifin_rate_lock_get(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *c = snd_kcontrol_chip(kcontrol);
	struct axg_spdifin *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.integer.value[0] = axg_spdifin_get_rate(priv);

	return 0;
}