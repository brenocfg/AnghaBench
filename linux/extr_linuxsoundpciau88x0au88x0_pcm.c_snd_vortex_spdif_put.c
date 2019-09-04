#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int spdif_sr; } ;
typedef  TYPE_3__ vortex_t ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int* status; } ;
struct TYPE_7__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int IEC958_AES3_CON_FS ; 
#define  IEC958_AES3_CON_FS_32000 130 
#define  IEC958_AES3_CON_FS_44100 129 
#define  IEC958_AES3_CON_FS_48000 128 
 TYPE_3__* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  vortex_spdif_init (TYPE_3__*,int,int) ; 

__attribute__((used)) static int snd_vortex_spdif_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	int spdif_sr = 48000;
	switch (ucontrol->value.iec958.status[3] & IEC958_AES3_CON_FS) {
	case IEC958_AES3_CON_FS_32000: spdif_sr = 32000; break;
	case IEC958_AES3_CON_FS_44100: spdif_sr = 44100; break;
	case IEC958_AES3_CON_FS_48000: spdif_sr = 48000; break;
	}
	if (spdif_sr == vortex->spdif_sr)
		return 0;
	vortex->spdif_sr = spdif_sr;
	vortex_spdif_init(vortex, vortex->spdif_sr, 1);
	return 1;
}