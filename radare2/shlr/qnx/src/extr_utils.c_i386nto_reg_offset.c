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
 int ARRAY_SIZE (int*) ; 
 int* i386nto_gregset_reg_offset ; 

int i386nto_reg_offset (int regnum) {
	if (regnum >= 0 && regnum < ARRAY_SIZE (i386nto_gregset_reg_offset))
		return i386nto_gregset_reg_offset[regnum];

	return -1;
}