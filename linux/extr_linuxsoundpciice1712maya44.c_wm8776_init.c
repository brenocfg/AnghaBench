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
struct snd_wm8776 {unsigned int addr; int switch_bits; } ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int WM_SW_DAC ; 
 int /*<<< orphan*/  wm8776_write (struct snd_ice1712*,struct snd_wm8776*,unsigned char,unsigned short) ; 

__attribute__((used)) static void wm8776_init(struct snd_ice1712 *ice,
			struct snd_wm8776 *wm, unsigned int addr)
{
	static const unsigned short inits_wm8776[] = {
		0x02, 0x100, /* R2: headphone L+R muted + update */
		0x05, 0x100, /* R5: DAC output L+R muted + update */
		0x06, 0x000, /* R6: DAC output phase normal */
		0x07, 0x091, /* R7: DAC enable zero cross detection,
				normal output */
		0x08, 0x000, /* R8: DAC soft mute off */
		0x09, 0x000, /* R9: no deemph, DAC zero detect disabled */
		0x0a, 0x022, /* R10: DAC I2C mode, std polarities, 24bit */
		0x0b, 0x022, /* R11: ADC I2C mode, std polarities, 24bit,
				highpass filter enabled */
		0x0c, 0x042, /* R12: ADC+DAC slave, ADC+DAC 44,1kHz */
		0x0d, 0x000, /* R13: all power up */
		0x0e, 0x100, /* R14: ADC left muted,
				enable zero cross detection */
		0x0f, 0x100, /* R15: ADC right muted,
				enable zero cross detection */
			     /* R16: ALC...*/
		0x11, 0x000, /* R17: disable ALC */
			     /* R18: ALC...*/
			     /* R19: noise gate...*/
		0x15, 0x000, /* R21: ADC input mux init, mute all inputs */
		0x16, 0x001, /* R22: output mux, select DAC */
		0xff, 0xff
	};

	const unsigned short *ptr;
	unsigned char reg;
	unsigned short data;

	wm->addr = addr;
	/* enable DAC output; mute bypass, aux & all inputs */
	wm->switch_bits = (1 << WM_SW_DAC);

	ptr = inits_wm8776;
	while (*ptr != 0xff) {
		reg = *ptr++;
		data = *ptr++;
		wm8776_write(ice, wm, reg, data);
	}
}