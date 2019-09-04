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
 int NR_PHYS_CTRS ; 
 int ps3_get_ctr_size (int,int) ; 
 int ps3_read_phys_ctr (int,int) ; 

u32 ps3_read_ctr(u32 cpu, u32 ctr)
{
	u32 val;
	u32 phys_ctr = ctr & (NR_PHYS_CTRS - 1);

	val = ps3_read_phys_ctr(cpu, phys_ctr);

	if (ps3_get_ctr_size(cpu, phys_ctr) == 16)
		val = (ctr < NR_PHYS_CTRS) ? (val >> 16) : (val & 0xffff);

	return val;
}