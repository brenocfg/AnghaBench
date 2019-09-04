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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_FORMAT ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE ; 
 unsigned char VT1724_MT_I2S_MCLK_128X ; 
 unsigned char VT1724_SPDIF_MASTER ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stdclock_set_spdif_clock(struct snd_ice1712 *ice, int type)
{
	unsigned char oval;
	unsigned char i2s_oval;
	oval = inb(ICEMT1724(ice, RATE));
	outb(oval | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));
	/* setting 256fs */
	i2s_oval = inb(ICEMT1724(ice, I2S_FORMAT));
	outb(i2s_oval & ~VT1724_MT_I2S_MCLK_128X, ICEMT1724(ice, I2S_FORMAT));
	return 0;
}