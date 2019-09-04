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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 iwl_get_dma_hi_addr(dma_addr_t addr)
{
	return (sizeof(addr) > sizeof(u32) ? upper_32_bits(addr) : 0) & 0xF;
}