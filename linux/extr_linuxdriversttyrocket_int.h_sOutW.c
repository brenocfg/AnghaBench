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
 int /*<<< orphan*/  outw_p (unsigned short,unsigned short) ; 

__attribute__((used)) static inline void sOutW(unsigned short port, unsigned short value)
{
#ifdef ROCKET_DEBUG_IO
	printk(KERN_DEBUG "sOutW(%x, %x)...\n", port, value);
#endif
	outw_p(value, port);
}