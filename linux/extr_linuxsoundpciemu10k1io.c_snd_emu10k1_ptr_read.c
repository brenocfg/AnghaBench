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
struct snd_emu10k1 {int /*<<< orphan*/  emu_lock; scalar_t__ port; scalar_t__ audigy; } ;

/* Variables and functions */
 unsigned int A_PTR_ADDRESS_MASK ; 
 scalar_t__ DATA ; 
 scalar_t__ PTR ; 
 unsigned int PTR_ADDRESS_MASK ; 
 unsigned int PTR_CHANNELNUM_MASK ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned int snd_emu10k1_ptr_read(struct snd_emu10k1 * emu, unsigned int reg, unsigned int chn)
{
	unsigned long flags;
	unsigned int regptr, val;
	unsigned int mask;

	mask = emu->audigy ? A_PTR_ADDRESS_MASK : PTR_ADDRESS_MASK;
	regptr = ((reg << 16) & mask) | (chn & PTR_CHANNELNUM_MASK);

	if (reg & 0xff000000) {
		unsigned char size, offset;
		
		size = (reg >> 24) & 0x3f;
		offset = (reg >> 16) & 0x1f;
		mask = ((1 << size) - 1) << offset;
		
		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		val = inl(emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		
		return (val & mask) >> offset;
	} else {
		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		val = inl(emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		return val;
	}
}