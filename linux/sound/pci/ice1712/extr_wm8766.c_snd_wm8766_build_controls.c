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
struct snd_wm8766 {TYPE_1__* ctl; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int WM8766_CTL_COUNT ; 
 int snd_wm8766_add_control (struct snd_wm8766*,int) ; 

int snd_wm8766_build_controls(struct snd_wm8766 *wm)
{
	int err, i;

	for (i = 0; i < WM8766_CTL_COUNT; i++)
		if (wm->ctl[i].name) {
			err = snd_wm8766_add_control(wm, i);
			if (err < 0)
				return err;
		}

	return 0;
}