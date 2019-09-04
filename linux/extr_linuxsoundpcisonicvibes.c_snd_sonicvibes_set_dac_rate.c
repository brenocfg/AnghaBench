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
 int SV_FULLRATE ; 
 int /*<<< orphan*/  SV_IREG_PCM_RATE_HIGH ; 
 int /*<<< orphan*/  SV_IREG_PCM_RATE_LOW ; 
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sonicvibes_set_dac_rate(struct sonicvibes * sonic, unsigned int rate)
{
	unsigned int div;
	unsigned long flags;

	div = (rate * 65536 + SV_FULLRATE / 2) / SV_FULLRATE;
	if (div > 65535)
		div = 65535;
	spin_lock_irqsave(&sonic->reg_lock, flags);
	snd_sonicvibes_out1(sonic, SV_IREG_PCM_RATE_HIGH, div >> 8);
	snd_sonicvibes_out1(sonic, SV_IREG_PCM_RATE_LOW, div);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
}