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
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_4__ {int count; } ;
struct link_slave {scalar_t__* vals; TYPE_1__ info; } ;

/* Variables and functions */
 int slave_init (struct link_slave*) ; 
 int slave_put_val (struct link_slave*,struct snd_ctl_elem_value*) ; 
 struct link_slave* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int slave_put(struct snd_kcontrol *kcontrol,
		     struct snd_ctl_elem_value *ucontrol)
{
	struct link_slave *slave = snd_kcontrol_chip(kcontrol);
	int err, ch, changed = 0;

	err = slave_init(slave);
	if (err < 0)
		return err;
	for (ch = 0; ch < slave->info.count; ch++) {
		if (slave->vals[ch] != ucontrol->value.integer.value[ch]) {
			changed = 1;
			slave->vals[ch] = ucontrol->value.integer.value[ch];
		}
	}
	if (!changed)
		return 0;
	err = slave_put_val(slave, ucontrol);
	if (err < 0)
		return err;
	return 1;
}