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
typedef  int u32 ;

/* Variables and functions */
 int cmpxchg (int*,int,int) ; 

__attribute__((used)) static int replace_u32(u32 *address, u32 mask, u32 new)
{
	u32 old, tmp;

	do {
		old = *address;
		tmp = (old & mask) ^ new;
		if (old == tmp)
			return 0;
	} while (cmpxchg(address, old, tmp) != old);

	return 1;
}