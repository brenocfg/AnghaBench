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
struct snd_wm8766 {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int WM8766_REG_RESET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_wm8766_default_ctl ; 
 int /*<<< orphan*/  snd_wm8766_write (struct snd_wm8766*,int,int const) ; 
 int /*<<< orphan*/  udelay (int) ; 

void snd_wm8766_init(struct snd_wm8766 *wm)
{
	int i;
	static const u16 default_values[] = {
		0x000, 0x100,
		0x120, 0x000,
		0x000, 0x100, 0x000, 0x100, 0x000,
		0x000, 0x080,
	};

	memcpy(wm->ctl, snd_wm8766_default_ctl, sizeof(wm->ctl));

	snd_wm8766_write(wm, WM8766_REG_RESET, 0x00); /* reset */
	udelay(10);
	/* load defaults */
	for (i = 0; i < ARRAY_SIZE(default_values); i++)
		snd_wm8766_write(wm, i, default_values[i]);
}