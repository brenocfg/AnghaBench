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
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  snd_sonicvibes_pll (unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sonicvibes_setpll(struct sonicvibes * sonic,
                                  unsigned char reg,
                                  unsigned int rate)
{
	unsigned long flags;
	unsigned int r, m, n;

	snd_sonicvibes_pll(rate, &r, &m, &n);
	if (sonic != NULL) {
		spin_lock_irqsave(&sonic->reg_lock, flags);
		snd_sonicvibes_out1(sonic, reg, m);
		snd_sonicvibes_out1(sonic, reg + 1, r | n);
		spin_unlock_irqrestore(&sonic->reg_lock, flags);
	}
}