#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * mixplayb; TYPE_4__* dma_adb; struct pcm_vol* pcm_vol; } ;
typedef  TYPE_5__ vortex_t ;
struct TYPE_9__ {int subdevice; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_10__ {unsigned char* value; } ;
struct TYPE_11__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct pcm_vol {unsigned char* vol; size_t dma; int* mixin; scalar_t__ active; } ;
struct TYPE_12__ {int nr_ch; } ;

/* Variables and functions */
 scalar_t__ VORTEX_IS_QUAD (TYPE_5__*) ; 
 TYPE_5__* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  vortex_mix_setinputvolumebyte (TYPE_5__*,int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static int snd_vortex_pcm_vol_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	int i;
	int changed = 0;
	int mixin;
	unsigned char vol;
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	int subdev = kcontrol->id.subdevice;
	struct pcm_vol *p = &vortex->pcm_vol[subdev];
	int max_chn = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
	for (i = 0; i < max_chn; i++) {
		if (p->vol[i] != ucontrol->value.integer.value[i]) {
			p->vol[i] = ucontrol->value.integer.value[i];
			if (p->active) {
				switch (vortex->dma_adb[p->dma].nr_ch) {
				case 1:
					mixin = p->mixin[0];
					break;
				case 2:
				default:
					mixin = p->mixin[(i < 2) ? i : (i - 2)];
					break;
				case 4:
					mixin = p->mixin[i];
					break;
				}
				vol = p->vol[i];
				vortex_mix_setinputvolumebyte(vortex,
					vortex->mixplayb[i], mixin, vol);
			}
			changed = 1;
		}
	}
	return changed;
}