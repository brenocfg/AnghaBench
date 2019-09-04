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
typedef  int /*<<< orphan*/  io_port ;

/* Variables and functions */
 unsigned char Inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Outb (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  iolock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned char InReg(io_port port, unsigned char reg)
{
	unsigned long flags;
	unsigned char r;

	spin_lock_irqsave(&iolock, flags);	
#ifdef SCC_LDELAY
	Outb(port, reg);
	udelay(SCC_LDELAY);
	r=Inb(port);
	udelay(SCC_LDELAY);
#else
	Outb(port, reg);
	r=Inb(port);
#endif
	spin_unlock_irqrestore(&iolock, flags);
	return r;
}