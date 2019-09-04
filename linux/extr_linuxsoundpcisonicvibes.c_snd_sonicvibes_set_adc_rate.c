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
struct sonicvibes {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_IREG_ADC_ALT_RATE ; 
 int /*<<< orphan*/  SV_IREG_ADC_CLOCK ; 
 int /*<<< orphan*/  SV_IREG_ADC_PLL ; 
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_sonicvibes_setpll (struct sonicvibes*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sonicvibes_set_adc_rate(struct sonicvibes * sonic, unsigned int rate)
{
	unsigned long flags;
	unsigned int div;
	unsigned char clock;

	div = 48000 / rate;
	if (div > 8)
		div = 8;
	if ((48000 / div) == rate) {	/* use the alternate clock */
		clock = 0x10;
	} else {			/* use the PLL source */
		clock = 0x00;
		snd_sonicvibes_setpll(sonic, SV_IREG_ADC_PLL, rate);
	}
	spin_lock_irqsave(&sonic->reg_lock, flags);
	snd_sonicvibes_out1(sonic, SV_IREG_ADC_ALT_RATE, (div - 1) << 4);
	snd_sonicvibes_out1(sonic, SV_IREG_ADC_CLOCK, clock);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
}