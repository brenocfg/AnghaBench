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
struct xsk_queue {int chunk_mask; int /*<<< orphan*/  invalid_descs; } ;
struct xdp_umem {int flags; int chunk_size_nohr; } ;
struct xdp_desc {int addr; int len; scalar_t__ options; } ;

/* Variables and functions */
 int XDP_UMEM_UNALIGNED_CHUNK_FLAG ; 
 int /*<<< orphan*/  xskq_is_valid_addr (struct xsk_queue*,int) ; 
 int /*<<< orphan*/  xskq_is_valid_addr_unaligned (struct xsk_queue*,int,int,struct xdp_umem*) ; 

__attribute__((used)) static inline bool xskq_is_valid_desc(struct xsk_queue *q, struct xdp_desc *d,
				      struct xdp_umem *umem)
{
	if (umem->flags & XDP_UMEM_UNALIGNED_CHUNK_FLAG) {
		if (!xskq_is_valid_addr_unaligned(q, d->addr, d->len, umem))
			return false;

		if (d->len > umem->chunk_size_nohr || d->options) {
			q->invalid_descs++;
			return false;
		}

		return true;
	}

	if (!xskq_is_valid_addr(q, d->addr))
		return false;

	if (((d->addr + d->len) & q->chunk_mask) != (d->addr & q->chunk_mask) ||
	    d->options) {
		q->invalid_descs++;
		return false;
	}

	return true;
}