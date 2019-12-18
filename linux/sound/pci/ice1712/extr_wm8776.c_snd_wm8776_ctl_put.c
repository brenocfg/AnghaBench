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
typedef  int u16 ;
struct snd_wm8776 {int* regs; TYPE_3__* ctl; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int flags; int max; int min; size_t reg1; int mask1; size_t reg2; int mask2; int /*<<< orphan*/  (* set ) (struct snd_wm8776*,int,int) ;} ;

/* Variables and functions */
 int WM8776_FLAG_INVERT ; 
 int WM8776_FLAG_STEREO ; 
 int WM8776_FLAG_VOL_UPDATE ; 
 int WM8776_VOL_UPDATE ; 
 int __ffs (int) ; 
 struct snd_wm8776* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_wm8776_write (struct snd_wm8776*,size_t,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_wm8776*,int,int) ; 

__attribute__((used)) static int snd_wm8776_ctl_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	int n = kcontrol->private_value;
	u16 val, regval1, regval2;

	/* this also works for enum because value is a union */
	regval1 = ucontrol->value.integer.value[0];
	regval2 = ucontrol->value.integer.value[1];
	if (wm->ctl[n].flags & WM8776_FLAG_INVERT) {
		regval1 = wm->ctl[n].max - (regval1 - wm->ctl[n].min);
		regval2 = wm->ctl[n].max - (regval2 - wm->ctl[n].min);
	}
	if (wm->ctl[n].set)
		wm->ctl[n].set(wm, regval1, regval2);
	else {
		val = wm->regs[wm->ctl[n].reg1] & ~wm->ctl[n].mask1;
		val |= regval1 << __ffs(wm->ctl[n].mask1);
		/* both stereo controls in one register */
		if (wm->ctl[n].flags & WM8776_FLAG_STEREO &&
				wm->ctl[n].reg1 == wm->ctl[n].reg2) {
			val &= ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
		}
		snd_wm8776_write(wm, wm->ctl[n].reg1, val);
		/* stereo controls in different registers */
		if (wm->ctl[n].flags & WM8776_FLAG_STEREO &&
				wm->ctl[n].reg1 != wm->ctl[n].reg2) {
			val = wm->regs[wm->ctl[n].reg2] & ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
			if (wm->ctl[n].flags & WM8776_FLAG_VOL_UPDATE)
				val |= WM8776_VOL_UPDATE;
			snd_wm8776_write(wm, wm->ctl[n].reg2, val);
		}
	}

	return 0;
}