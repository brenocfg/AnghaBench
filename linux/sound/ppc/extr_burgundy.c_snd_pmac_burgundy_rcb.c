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
struct snd_pmac {int /*<<< orphan*/  reg_lock; TYPE_1__* awacs; } ;
struct TYPE_2__ {int /*<<< orphan*/  codec_stat; int /*<<< orphan*/  codec_ctrl; } ;

/* Variables and functions */
 int in_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  snd_pmac_burgundy_busy_wait (struct snd_pmac*) ; 
 int /*<<< orphan*/  snd_pmac_burgundy_extend_wait (struct snd_pmac*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned
snd_pmac_burgundy_rcb(struct snd_pmac *chip, unsigned int addr)
{
	unsigned val = 0;
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);

	out_le32(&chip->awacs->codec_ctrl, addr + 0x100000);
	snd_pmac_burgundy_busy_wait(chip);
	snd_pmac_burgundy_extend_wait(chip);
	val += (in_le32(&chip->awacs->codec_stat) >> 4) & 0xff;

	spin_unlock_irqrestore(&chip->reg_lock, flags);

	return val;
}