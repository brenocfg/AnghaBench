#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int spdif_sr; } ;
typedef  TYPE_3__ vortex_t ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int* status; } ;
struct TYPE_6__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int IEC958_AES1_CON_DIGDIGCONV_ID ; 
 int IEC958_AES1_CON_ORIGINAL ; 
 int IEC958_AES3_CON_FS_32000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 TYPE_3__* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_vortex_spdif_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	ucontrol->value.iec958.status[0] = 0x00;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_ORIGINAL|IEC958_AES1_CON_DIGDIGCONV_ID;
	ucontrol->value.iec958.status[2] = 0x00;
	switch (vortex->spdif_sr) {
	case 32000: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_32000; break;
	case 44100: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_44100; break;
	case 48000: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_48000; break;
	}
	return 0;
}