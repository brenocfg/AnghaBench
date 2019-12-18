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
typedef  int u64 ;
struct xdp_umem {TYPE_1__* pages; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long XSK_NEXT_PG_CONTIG_MASK ; 

__attribute__((used)) static inline bool xskq_crosses_non_contig_pg(struct xdp_umem *umem, u64 addr,
					      u64 length)
{
	bool cross_pg = (addr & (PAGE_SIZE - 1)) + length > PAGE_SIZE;
	bool next_pg_contig =
		(unsigned long)umem->pages[(addr >> PAGE_SHIFT)].addr &
			XSK_NEXT_PG_CONTIG_MASK;

	return cross_pg && !next_pg_contig;
}