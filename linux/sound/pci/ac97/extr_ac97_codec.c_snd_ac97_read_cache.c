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
struct snd_ac97 {unsigned short* regs; TYPE_2__* bus; int /*<<< orphan*/  reg_accessed; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {unsigned short (* read ) (struct snd_ac97*,unsigned short) ;} ;

/* Variables and functions */
 unsigned short stub1 (struct snd_ac97*,unsigned short) ; 
 int /*<<< orphan*/  test_bit (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned short snd_ac97_read_cache(struct snd_ac97 *ac97, unsigned short reg)
{
	if (! test_bit(reg, ac97->reg_accessed)) {
		ac97->regs[reg] = ac97->bus->ops->read(ac97, reg);
		// set_bit(reg, ac97->reg_accessed);
	}
	return ac97->regs[reg];
}