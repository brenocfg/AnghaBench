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
 unsigned long IO_TLB_DEFAULT_SIZE ; 
 unsigned long IO_TLB_SHIFT ; 
 unsigned long io_tlb_nslabs ; 

unsigned long swiotlb_size_or_default(void)
{
	unsigned long size;

	size = io_tlb_nslabs << IO_TLB_SHIFT;

	return size ? size : (IO_TLB_DEFAULT_SIZE);
}