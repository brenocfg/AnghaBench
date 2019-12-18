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
 unsigned int SH_MAX_REGS ; 
 char const** sh_regs_table ; 

const char *get_arch_regstr(unsigned int n)
{
	return (n < SH_MAX_REGS) ? sh_regs_table[n] : NULL;
}