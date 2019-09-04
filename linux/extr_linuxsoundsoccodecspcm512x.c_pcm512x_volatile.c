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
struct device {int dummy; } ;

/* Variables and functions */
#define  PCM512x_ANALOG_MUTE_DET 138 
#define  PCM512x_CLOCK_STATUS 137 
#define  PCM512x_CRAM_CTRL 136 
#define  PCM512x_DIGITAL_MUTE_DET 135 
#define  PCM512x_GPIN 134 
#define  PCM512x_OVERFLOW 133 
#define  PCM512x_PLL_EN 132 
#define  PCM512x_RATE_DET_1 131 
#define  PCM512x_RATE_DET_2 130 
#define  PCM512x_RATE_DET_3 129 
#define  PCM512x_RATE_DET_4 128 

__attribute__((used)) static bool pcm512x_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case PCM512x_PLL_EN:
	case PCM512x_OVERFLOW:
	case PCM512x_RATE_DET_1:
	case PCM512x_RATE_DET_2:
	case PCM512x_RATE_DET_3:
	case PCM512x_RATE_DET_4:
	case PCM512x_CLOCK_STATUS:
	case PCM512x_ANALOG_MUTE_DET:
	case PCM512x_GPIN:
	case PCM512x_DIGITAL_MUTE_DET:
	case PCM512x_CRAM_CTRL:
		return true;
	default:
		/* There are 256 raw register addresses */
		return reg < 0xff;
	}
}