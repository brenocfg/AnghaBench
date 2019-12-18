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
#define  WM_ADC_MUX 132 
#define  WM_DAC_CTRL1 131 
#define  WM_DAC_MUTE 130 
#define  WM_POWERDOWN 129 
#define  WM_RESET 128 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned short,unsigned short) ; 

__attribute__((used)) static void wm8776_init(struct snd_ice1712 *ice)
{
	static unsigned short wm8776_inits[] = {
		/* These come first to reduce init pop noise */
		WM_ADC_MUX,	0x0003,	/* ADC mute */
		/* 0x00c0 replaced by 0x0003 */
		
		WM_DAC_MUTE,	0x0001,	/* DAC softmute */
		WM_DAC_CTRL1,	0x0000,	/* DAC mute */

		WM_POWERDOWN,	0x0008,	/* All power-up except HP */
		WM_RESET,	0x0000,	/* reset */
	};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(wm8776_inits); i += 2)
		wm_put(ice, wm8776_inits[i], wm8776_inits[i + 1]);
}