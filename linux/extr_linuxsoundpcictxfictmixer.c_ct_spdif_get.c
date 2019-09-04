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
struct TYPE_3__ {unsigned int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ct_atc {int /*<<< orphan*/  (* spdif_out_get_status ) (struct ct_atc*,unsigned int*) ;} ;

/* Variables and functions */
 unsigned int SNDRV_PCM_DEFAULT_CON_SPDIF ; 
 struct ct_atc* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*,unsigned int*) ; 

__attribute__((used)) static int ct_spdif_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct ct_atc *atc = snd_kcontrol_chip(kcontrol);
	unsigned int status;

	atc->spdif_out_get_status(atc, &status);

	if (status == 0)
		status = SNDRV_PCM_DEFAULT_CON_SPDIF;

	ucontrol->value.iec958.status[0] = (status >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (status >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (status >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (status >> 24) & 0xff;

	return 0;
}