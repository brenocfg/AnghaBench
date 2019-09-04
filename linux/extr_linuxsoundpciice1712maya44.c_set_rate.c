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
struct snd_maya44 {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * wm; } ;
struct snd_ice1712 {struct snd_maya44* spec; } ;

/* Variables and functions */
 unsigned int WM8776_CLOCK_RATIO_128FS ; 
 unsigned int WM8776_CLOCK_RATIO_256FS ; 
 unsigned int WM8776_CLOCK_RATIO_384FS ; 
 unsigned int WM8776_CLOCK_RATIO_512FS ; 
 unsigned int WM8776_CLOCK_RATIO_768FS ; 
 int /*<<< orphan*/  WM8776_REG_MASTER_MODE_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  wm8776_write_bits (struct snd_ice1712*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void set_rate(struct snd_ice1712 *ice, unsigned int rate)
{
	struct snd_maya44 *chip = ice->spec;
	unsigned int ratio, adc_ratio, val;
	int i;

	switch (rate) {
	case 192000:
		ratio = WM8776_CLOCK_RATIO_128FS;
		break;
	case 176400:
		ratio = WM8776_CLOCK_RATIO_128FS;
		break;
	case 96000:
		ratio = WM8776_CLOCK_RATIO_256FS;
		break;
	case 88200:
		ratio = WM8776_CLOCK_RATIO_384FS;
		break;
	case 48000:
		ratio = WM8776_CLOCK_RATIO_512FS;
		break;
	case 44100:
		ratio = WM8776_CLOCK_RATIO_512FS;
		break;
	case 32000:
		ratio = WM8776_CLOCK_RATIO_768FS;
		break;
	case 0:
		/* no hint - S/PDIF input is master, simply return */
		return;
	default:
		snd_BUG();
		return;
	}

	/*
	 * this currently sets the same rate for ADC and DAC, but limits
	 * ADC rate to 256X (96kHz). For 256X mode (96kHz), this sets ADC
	 * oversampling to 64x, as recommended by WM8776 datasheet.
	 * Setting the rate is not really necessary in slave mode.
	 */
	adc_ratio = ratio;
	if (adc_ratio < WM8776_CLOCK_RATIO_256FS)
		adc_ratio = WM8776_CLOCK_RATIO_256FS;

	val = adc_ratio;
	if (adc_ratio == WM8776_CLOCK_RATIO_256FS)
		val |= 8;
	val |= ratio << 4;

	mutex_lock(&chip->mutex);
	for (i = 0; i < 2; i++)
		wm8776_write_bits(ice, &chip->wm[i],
				  WM8776_REG_MASTER_MODE_CONTROL,
				  0x180, val);
	mutex_unlock(&chip->mutex);
}