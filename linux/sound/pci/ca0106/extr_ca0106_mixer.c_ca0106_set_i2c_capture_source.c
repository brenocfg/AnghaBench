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
typedef  unsigned int u32 ;
struct snd_ca0106 {unsigned int** i2c_capture_volume; size_t i2c_capture_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_ATTEN_ADCL ; 
 int /*<<< orphan*/  ADC_ATTEN_ADCR ; 
 int /*<<< orphan*/  ADC_MUX ; 
 int /*<<< orphan*/  snd_ca0106_i2c_write (struct snd_ca0106*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ca0106_set_i2c_capture_source(struct snd_ca0106 *emu,
					  unsigned int val, int force)
{
	unsigned int ngain, ogain;
	u32 source;

	snd_ca0106_i2c_write(emu, ADC_MUX, 0); /* Mute input */
	ngain = emu->i2c_capture_volume[val][0]; /* Left */
	ogain = emu->i2c_capture_volume[emu->i2c_capture_source][0]; /* Left */
	if (force || ngain != ogain)
		snd_ca0106_i2c_write(emu, ADC_ATTEN_ADCL, ngain & 0xff);
	ngain = emu->i2c_capture_volume[val][1]; /* Right */
	ogain = emu->i2c_capture_volume[emu->i2c_capture_source][1]; /* Right */
	if (force || ngain != ogain)
		snd_ca0106_i2c_write(emu, ADC_ATTEN_ADCR, ngain & 0xff);
	source = 1 << val;
	snd_ca0106_i2c_write(emu, ADC_MUX, source); /* Set source */
	emu->i2c_capture_source = val;
}