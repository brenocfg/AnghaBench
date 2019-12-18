#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct snd_wm8776 {int* regs; int /*<<< orphan*/  agc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8776_AGC_ALC_L ; 
 int /*<<< orphan*/  WM8776_AGC_ALC_R ; 
 int /*<<< orphan*/  WM8776_AGC_ALC_STEREO ; 
 int /*<<< orphan*/  WM8776_AGC_LIM ; 
 int /*<<< orphan*/  WM8776_AGC_OFF ; 
 int WM8776_ALC1_LCSEL_ALCL ; 
 int WM8776_ALC1_LCSEL_ALCR ; 
 int WM8776_ALC1_LCSEL_ALCSTEREO ; 
 int WM8776_ALC1_LCT_MASK ; 
 int WM8776_ALC2_LCEN ; 
 size_t WM8776_REG_ALCCTRL1 ; 
 size_t WM8776_REG_ALCCTRL2 ; 
 int /*<<< orphan*/  snd_wm8776_update_agc_ctl (struct snd_wm8776*) ; 
 int /*<<< orphan*/  snd_wm8776_write (struct snd_wm8776*,size_t,int) ; 

__attribute__((used)) static void snd_wm8776_set_agc(struct snd_wm8776 *wm, u16 agc, u16 nothing)
{
	u16 alc1 = wm->regs[WM8776_REG_ALCCTRL1] & ~WM8776_ALC1_LCT_MASK;
	u16 alc2 = wm->regs[WM8776_REG_ALCCTRL2] & ~WM8776_ALC2_LCEN;

	switch (agc) {
	case 0:	/* Off */
		wm->agc_mode = WM8776_AGC_OFF;
		break;
	case 1: /* Limiter */
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_LIM;
		break;
	case 2: /* ALC Right */
		alc1 |= WM8776_ALC1_LCSEL_ALCR;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_R;
		break;
	case 3: /* ALC Left */
		alc1 |= WM8776_ALC1_LCSEL_ALCL;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_L;
		break;
	case 4: /* ALC Stereo */
		alc1 |= WM8776_ALC1_LCSEL_ALCSTEREO;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_STEREO;
		break;
	}
	snd_wm8776_write(wm, WM8776_REG_ALCCTRL1, alc1);
	snd_wm8776_write(wm, WM8776_REG_ALCCTRL2, alc2);
	snd_wm8776_update_agc_ctl(wm);
}