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

/* Variables and functions */
 unsigned int CLK_44EN_RATE ; 
 unsigned int CLK_48EN_RATE ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_clk44gpio ; 
 int /*<<< orphan*/  snd_clk48gpio ; 

__attribute__((used)) static unsigned int snd_rpi_wm8804_enable_clock(unsigned int samplerate)
{
	switch (samplerate) {
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
		gpiod_set_value_cansleep(snd_clk44gpio, 1);
		gpiod_set_value_cansleep(snd_clk48gpio, 0);
		return CLK_44EN_RATE;
	default:
		gpiod_set_value_cansleep(snd_clk48gpio, 1);
		gpiod_set_value_cansleep(snd_clk44gpio, 0);
		return CLK_48EN_RATE;
	}
}