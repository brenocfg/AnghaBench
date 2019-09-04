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
typedef  int u_int ;
typedef  scalar_t__ u_char ;

/* Variables and functions */
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 scalar_t__ tcic_base ; 

__attribute__((used)) static void tcic_setl(u_char reg, u_int data)
{
#ifdef DEBUG_X
    printk(KERN_DEBUG "tcic_setl(%#x, %#lx)\n", tcic_base+reg, data);
#endif
    outw(data & 0xffff, tcic_base+reg);
    outw(data >> 16, tcic_base+reg+2);
}