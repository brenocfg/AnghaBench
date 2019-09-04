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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ct_atc {int /*<<< orphan*/  (* spdif_out_set_status ) (struct ct_atc*,unsigned int) ;int /*<<< orphan*/  (* spdif_out_get_status ) (struct ct_atc*,unsigned int*) ;} ;

/* Variables and functions */
 struct ct_atc* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*,unsigned int*) ; 
 int /*<<< orphan*/  stub2 (struct ct_atc*,unsigned int) ; 

__attribute__((used)) static int ct_spdif_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct ct_atc *atc = snd_kcontrol_chip(kcontrol);
	int change;
	unsigned int status, old_status;

	status = (ucontrol->value.iec958.status[0] << 0) |
		 (ucontrol->value.iec958.status[1] << 8) |
		 (ucontrol->value.iec958.status[2] << 16) |
		 (ucontrol->value.iec958.status[3] << 24);

	atc->spdif_out_get_status(atc, &old_status);
	change = (old_status != status);
	if (change)
		atc->spdif_out_set_status(atc, status);

	return change;
}