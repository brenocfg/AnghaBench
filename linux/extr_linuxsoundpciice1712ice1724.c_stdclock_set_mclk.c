#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* data; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_FORMAT ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t ICE_EEP2_ACLINK ; 
 int VT1724_CFG_PRO_I2S ; 
 unsigned char VT1724_MT_I2S_MCLK_128X ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char stdclock_set_mclk(struct snd_ice1712 *ice,
				       unsigned int rate)
{
	unsigned char val, old;
	/* check MT02 */
	if (ice->eeprom.data[ICE_EEP2_ACLINK] & VT1724_CFG_PRO_I2S) {
		val = old = inb(ICEMT1724(ice, I2S_FORMAT));
		if (rate > 96000)
			val |= VT1724_MT_I2S_MCLK_128X; /* 128x MCLK */
		else
			val &= ~VT1724_MT_I2S_MCLK_128X; /* 256x MCLK */
		if (val != old) {
			outb(val, ICEMT1724(ice, I2S_FORMAT));
			/* master clock changed */
			return 1;
		}
	}
	/* no change in master clock */
	return 0;
}