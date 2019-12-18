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
typedef  scalar_t__ u64 ;
struct xsk_queue {scalar_t__ size; int /*<<< orphan*/  invalid_descs; } ;
struct xdp_umem {int dummy; } ;

/* Variables and functions */
 scalar_t__ xsk_umem_add_offset_to_addr (scalar_t__) ; 
 scalar_t__ xsk_umem_extract_addr (scalar_t__) ; 
 scalar_t__ xskq_crosses_non_contig_pg (struct xdp_umem*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline bool xskq_is_valid_addr_unaligned(struct xsk_queue *q, u64 addr,
						u64 length,
						struct xdp_umem *umem)
{
	u64 base_addr = xsk_umem_extract_addr(addr);

	addr = xsk_umem_add_offset_to_addr(addr);
	if (base_addr >= q->size || addr >= q->size ||
	    xskq_crosses_non_contig_pg(umem, addr, length)) {
		q->invalid_descs++;
		return false;
	}

	return true;
}