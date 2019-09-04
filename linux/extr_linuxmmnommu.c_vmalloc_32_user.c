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
 void* vmalloc_user (unsigned long) ; 

void *vmalloc_32_user(unsigned long size)
{
	/*
	 * We'll have to sort out the ZONE_DMA bits for 64-bit,
	 * but for now this can simply use vmalloc_user() directly.
	 */
	return vmalloc_user(size);
}