#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct xdp_umem {TYPE_1__* pages; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ dma; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline dma_addr_t xdp_umem_get_dma(struct xdp_umem *umem, u64 addr)
{
	return umem->pages[addr >> PAGE_SHIFT].dma + (addr & (PAGE_SIZE - 1));
}