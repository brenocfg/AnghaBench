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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  Byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outl_p (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static inline void out32(unsigned short port, Byte_t *p)
{
	u32 value = get_unaligned_le32(p);
#ifdef ROCKET_DEBUG_IO
	printk(KERN_DEBUG "out32(%x, %lx)...\n", port, value);
#endif
	outl_p(value, port);
}