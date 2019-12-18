#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_wm8776 {int agc_mode; TYPE_1__* ctl; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  WM8776_AGC_ALC_L 132 
#define  WM8776_AGC_ALC_R 131 
#define  WM8776_AGC_ALC_STEREO 130 
#define  WM8776_AGC_LIM 129 
#define  WM8776_AGC_OFF 128 
 int WM8776_CTL_COUNT ; 
 int WM8776_FLAG_ALC ; 
 int WM8776_FLAG_LIM ; 
 int /*<<< orphan*/  snd_wm8776_activate_ctl (struct snd_wm8776*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_wm8776_update_agc_ctl(struct snd_wm8776 *wm)
{
	int i, flags_on = 0, flags_off = 0;

	switch (wm->agc_mode) {
	case WM8776_AGC_OFF:
		flags_off = WM8776_FLAG_LIM | WM8776_FLAG_ALC;
		break;
	case WM8776_AGC_LIM:
		flags_off = WM8776_FLAG_ALC;
		flags_on = WM8776_FLAG_LIM;
		break;
	case WM8776_AGC_ALC_R:
	case WM8776_AGC_ALC_L:
	case WM8776_AGC_ALC_STEREO:
		flags_off = WM8776_FLAG_LIM;
		flags_on = WM8776_FLAG_ALC;
		break;
	}

	for (i = 0; i < WM8776_CTL_COUNT; i++)
		if (wm->ctl[i].flags & flags_off)
			snd_wm8776_activate_ctl(wm, wm->ctl[i].name, false);
		else if (wm->ctl[i].flags & flags_on)
			snd_wm8776_activate_ctl(wm, wm->ctl[i].name, true);
}