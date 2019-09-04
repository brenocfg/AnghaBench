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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MBAR0_SWC_SIZE ; 
 scalar_t__ asd_mem_offs_swc () ; 

__attribute__((used)) static inline u32 asd_mem_offs_swb(void)
{
	return asd_mem_offs_swc() + MBAR0_SWC_SIZE + 0x20;
}