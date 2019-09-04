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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline void unpack_pointer(dma_addr_t ptr, u32 *r_low, u32 *r_high)
{
	*r_low = (u32)(ptr & 0xffffffff);
#if BITS_PER_LONG == 32
	*r_high = 0;
#else
	*r_high = (u32)((u64)ptr>>32);
#endif
}