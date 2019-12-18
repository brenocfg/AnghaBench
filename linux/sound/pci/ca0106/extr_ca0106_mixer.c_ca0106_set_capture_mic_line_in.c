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
typedef  int u32 ;
struct snd_ca0106 {scalar_t__ port; scalar_t__ capture_mic_line_in; } ;

/* Variables and functions */
 scalar_t__ GPIO ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void ca0106_set_capture_mic_line_in(struct snd_ca0106 *emu)
{
	u32 tmp;

	if (emu->capture_mic_line_in) {
		/* snd_ca0106_i2c_write(emu, ADC_MUX, 0); */ /* Mute input */
		tmp = inl(emu->port+GPIO) & ~0x400;
		tmp = tmp | 0x400;
		outl(tmp, emu->port+GPIO);
		/* snd_ca0106_i2c_write(emu, ADC_MUX, ADC_MUX_MIC); */
	} else {
		/* snd_ca0106_i2c_write(emu, ADC_MUX, 0); */ /* Mute input */
		tmp = inl(emu->port+GPIO) & ~0x400;
		outl(tmp, emu->port+GPIO);
		/* snd_ca0106_i2c_write(emu, ADC_MUX, ADC_MUX_LINEIN); */
	}
}