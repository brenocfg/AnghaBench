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
 int code16_sel ; 
 int cs_bitness (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int find_cs(int bitness)
{
	unsigned short my_cs;

	asm ("mov %%cs,%0" :  "=r" (my_cs));

	if (cs_bitness(my_cs) == bitness)
		return my_cs;
	if (cs_bitness(my_cs + (2 << 3)) == bitness)
		return my_cs + (2 << 3);
	if (my_cs > (2<<3) && cs_bitness(my_cs - (2 << 3)) == bitness)
	    return my_cs - (2 << 3);
	if (cs_bitness(code16_sel) == bitness)
		return code16_sel;

	printf("[WARN]\tCould not find %d-bit CS\n", bitness);
	return -1;
}