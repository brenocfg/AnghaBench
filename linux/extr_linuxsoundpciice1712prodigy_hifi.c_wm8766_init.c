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
 unsigned int ARRAY_SIZE (unsigned short*) ; 
#define  WM8766_DAC_CTRL 140 
#define  WM8766_DAC_CTRL2 139 
#define  WM8766_DAC_CTRL3 138 
#define  WM8766_INT_CTRL 137 
#define  WM8766_LDA1 136 
#define  WM8766_LDA2 135 
#define  WM8766_LDA3 134 
#define  WM8766_MUTE1 133 
#define  WM8766_MUTE2 132 
#define  WM8766_RDA1 131 
#define  WM8766_RDA2 130 
#define  WM8766_RDA3 129 
#define  WM8766_RESET 128 
 int /*<<< orphan*/  wm8766_spi_write (struct snd_ice1712*,unsigned short,unsigned short) ; 

__attribute__((used)) static void wm8766_init(struct snd_ice1712 *ice)
{
	static unsigned short wm8766_inits[] = {
		WM8766_RESET,	   0x0000,
		WM8766_DAC_CTRL,	0x0120,
		WM8766_INT_CTRL,	0x0022, /* I2S Normal Mode, 24 bit */
		WM8766_DAC_CTRL2,       0x0001,
		WM8766_DAC_CTRL3,       0x0080,
		WM8766_LDA1,	    0x0100,
		WM8766_LDA2,	    0x0100,
		WM8766_LDA3,	    0x0100,
		WM8766_RDA1,	    0x0100,
		WM8766_RDA2,	    0x0100,
		WM8766_RDA3,	    0x0100,
		WM8766_MUTE1,	   0x0000,
		WM8766_MUTE2,	   0x0000,
	};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(wm8766_inits); i += 2)
		wm8766_spi_write(ice, wm8766_inits[i], wm8766_inits[i + 1]);
}