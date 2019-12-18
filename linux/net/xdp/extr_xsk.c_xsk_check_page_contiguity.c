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
struct xdp_umem_page {scalar_t__ dma; scalar_t__ addr; } ;
struct xdp_umem {int npgs; struct xdp_umem_page* pages; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int XDP_ZEROCOPY ; 
 int XSK_NEXT_PG_CONTIG_SHIFT ; 

__attribute__((used)) static void xsk_check_page_contiguity(struct xdp_umem *umem, u32 flags)
{
	struct xdp_umem_page *pgs = umem->pages;
	int i, is_contig;

	for (i = 0; i < umem->npgs - 1; i++) {
		is_contig = (flags & XDP_ZEROCOPY) ?
			(pgs[i].dma + PAGE_SIZE == pgs[i + 1].dma) :
			(pgs[i].addr + PAGE_SIZE == pgs[i + 1].addr);
		pgs[i].addr += is_contig << XSK_NEXT_PG_CONTIG_SHIFT;
	}
}