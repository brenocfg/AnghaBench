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
struct TYPE_2__ {int chunk_mask; } ;
struct xsk_queue {int /*<<< orphan*/  invalid_descs; TYPE_1__ umem_props; } ;
struct xdp_desc {int addr; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  xskq_is_valid_addr (struct xsk_queue*,int) ; 

__attribute__((used)) static inline bool xskq_is_valid_desc(struct xsk_queue *q, struct xdp_desc *d)
{
	if (!xskq_is_valid_addr(q, d->addr))
		return false;

	if (((d->addr + d->len) & q->umem_props.chunk_mask) !=
	    (d->addr & q->umem_props.chunk_mask)) {
		q->invalid_descs++;
		return false;
	}

	return true;
}