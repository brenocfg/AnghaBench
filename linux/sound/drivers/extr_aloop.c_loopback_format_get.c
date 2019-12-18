#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t subdevice; size_t device; } ;
struct snd_kcontrol {TYPE_4__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct loopback {TYPE_3__** setup; } ;
struct TYPE_7__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 struct loopback* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int loopback_format_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.integer.value[0] =
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].format;
	return 0;
}