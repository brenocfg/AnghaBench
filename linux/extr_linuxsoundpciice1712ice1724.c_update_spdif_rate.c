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
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPDIF_CTRL ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_spdif_bits (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static void update_spdif_rate(struct snd_ice1712 *ice, unsigned int rate)
{
	unsigned int val, nval;
	unsigned long flags;

	spin_lock_irqsave(&ice->reg_lock, flags);
	nval = val = inw(ICEMT1724(ice, SPDIF_CTRL));
	nval &= ~(7 << 12);
	switch (rate) {
	case 44100: break;
	case 48000: nval |= 2 << 12; break;
	case 32000: nval |= 3 << 12; break;
	case 88200: nval |= 4 << 12; break;
	case 96000: nval |= 5 << 12; break;
	case 192000: nval |= 6 << 12; break;
	case 176400: nval |= 7 << 12; break;
	}
	if (val != nval)
		update_spdif_bits(ice, nval);
	spin_unlock_irqrestore(&ice->reg_lock, flags);
}