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
struct snd_wm8766 {int* regs; } ;

/* Variables and functions */
 int WM8766_IF_MASK ; 
 size_t WM8766_REG_IFCTRL ; 
 int /*<<< orphan*/  snd_wm8766_write (struct snd_wm8766*,size_t,int) ; 

void snd_wm8766_set_if(struct snd_wm8766 *wm, u16 dac)
{
	u16 val = wm->regs[WM8766_REG_IFCTRL] & ~WM8766_IF_MASK;

	dac &= WM8766_IF_MASK;
	snd_wm8766_write(wm, WM8766_REG_IFCTRL, val | dac);
}