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
typedef  scalar_t__ u16 ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_DAP_AVC_THRESHOLD ; 
 scalar_t__* avc_thr_db2reg ; 
 scalar_t__ snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int avc_get_threshold(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	int db, i;
	u16 reg = snd_soc_component_read32(component, SGTL5000_DAP_AVC_THRESHOLD);

	/* register value 0 => -96dB */
	if (!reg) {
		ucontrol->value.integer.value[0] = 96;
		ucontrol->value.integer.value[1] = 96;
		return 0;
	}

	/* get dB from register value (rounded down) */
	for (i = 0; avc_thr_db2reg[i] > reg; i++)
		;
	db = i;

	ucontrol->value.integer.value[0] = db;
	ucontrol->value.integer.value[1] = db;

	return 0;
}