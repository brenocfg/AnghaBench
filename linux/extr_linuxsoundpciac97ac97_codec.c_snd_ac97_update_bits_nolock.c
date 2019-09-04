#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {unsigned short* regs; int /*<<< orphan*/  reg_accessed; TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (struct snd_ac97*,unsigned short,unsigned short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short snd_ac97_read_cache (struct snd_ac97*,unsigned short) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*,unsigned short,unsigned short) ; 

int snd_ac97_update_bits_nolock(struct snd_ac97 *ac97, unsigned short reg,
				unsigned short mask, unsigned short value)
{
	int change;
	unsigned short old, new;

	old = snd_ac97_read_cache(ac97, reg);
	new = (old & ~mask) | (value & mask);
	change = old != new;
	if (change) {
		ac97->regs[reg] = new;
		ac97->bus->ops->write(ac97, reg, new);
	}
	set_bit(reg, ac97->reg_accessed);
	return change;
}