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
typedef  int u8 ;
struct snd_opl4 {int /*<<< orphan*/  reg_lock; scalar_t__ pcm_port; } ;

/* Variables and functions */
 int OPL4_MODE_BIT ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_ADDRESS_HIGH ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_ADDRESS_LOW ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_ADDRESS_MID ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_CONFIGURATION ; 
 int /*<<< orphan*/  OPL4_REG_MEMORY_DATA ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outsb (scalar_t__,char const*,int) ; 
 int snd_opl4_read (struct snd_opl4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_wait (struct snd_opl4*) ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_opl4_write_memory(struct snd_opl4 *opl4, const char *buf, int offset, int size)
{
	unsigned long flags;
	u8 memcfg;

	spin_lock_irqsave(&opl4->reg_lock, flags);

	memcfg = snd_opl4_read(opl4, OPL4_REG_MEMORY_CONFIGURATION);
	snd_opl4_write(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg | OPL4_MODE_BIT);

	snd_opl4_write(opl4, OPL4_REG_MEMORY_ADDRESS_HIGH, offset >> 16);
	snd_opl4_write(opl4, OPL4_REG_MEMORY_ADDRESS_MID, offset >> 8);
	snd_opl4_write(opl4, OPL4_REG_MEMORY_ADDRESS_LOW, offset);

	snd_opl4_wait(opl4);
	outb(OPL4_REG_MEMORY_DATA, opl4->pcm_port);
	snd_opl4_wait(opl4);
	outsb(opl4->pcm_port + 1, buf, size);

	snd_opl4_write(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg);

	spin_unlock_irqrestore(&opl4->reg_lock, flags);
}