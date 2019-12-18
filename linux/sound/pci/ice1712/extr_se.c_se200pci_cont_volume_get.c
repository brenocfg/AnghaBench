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
struct snd_kcontrol {int private_value; } ;
struct snd_ice1712 {struct se_spec* spec; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct se_spec {TYPE_1__* vol; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch2; int /*<<< orphan*/  ch1; } ;

/* Variables and functions */
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int se200pci_cont_volume_get(struct snd_kcontrol *kc,
				    struct snd_ctl_elem_value *uc)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kc);
	struct se_spec *spec = ice->spec;
	int n = kc->private_value;
	uc->value.integer.value[0] = spec->vol[n].ch1;
	uc->value.integer.value[1] = spec->vol[n].ch2;
	return 0;
}