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

/* Variables and functions */
 int inb (unsigned int) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 

__attribute__((used)) static int
snd_azf3328_io_reg_setb(unsigned reg, u8 mask, bool do_set)
{
	/* Well, strictly spoken, the inb/outb sequence isn't atomic
	   and would need locking. However we currently don't care
	   since it potentially complicates matters. */
	u8 prev = inb(reg), new;

	new = (do_set) ? (prev|mask) : (prev & ~mask);
	/* we need to always write the new value no matter whether it differs
	 * or not, since some register bits don't indicate their setting */
	outb(new, reg);
	if (new != prev)
		return 1;

	return 0;
}