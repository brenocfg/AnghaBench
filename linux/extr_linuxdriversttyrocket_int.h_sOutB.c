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

/* Variables and functions */
 int /*<<< orphan*/  outb_p (unsigned char,unsigned short) ; 

__attribute__((used)) static inline void sOutB(unsigned short port, unsigned char value)
{
#ifdef ROCKET_DEBUG_IO
	printk(KERN_DEBUG "sOutB(%x, %x)...\n", port, value);
#endif
	outb_p(value, port);
}