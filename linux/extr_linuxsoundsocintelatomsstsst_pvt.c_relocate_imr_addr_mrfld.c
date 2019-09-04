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
 int MRFLD_FW_VIRTUAL_BASE ; 

u32 relocate_imr_addr_mrfld(u32 base_addr)
{
	/* Get the difference from 512MB aligned base addr */
	/* relocate the base */
	base_addr = MRFLD_FW_VIRTUAL_BASE + (base_addr % (512 * 1024 * 1024));
	return base_addr;
}