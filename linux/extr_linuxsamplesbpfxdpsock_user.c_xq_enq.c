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
typedef  size_t u32 ;
struct xdp_uqueue {size_t mask; scalar_t__ cached_prod; scalar_t__* producer; struct xdp_desc* ring; } ;
struct xdp_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  u_smp_wmb () ; 
 unsigned int xq_nb_free (struct xdp_uqueue*,unsigned int) ; 

__attribute__((used)) static inline int xq_enq(struct xdp_uqueue *uq,
			 const struct xdp_desc *descs,
			 unsigned int ndescs)
{
	struct xdp_desc *r = uq->ring;
	unsigned int i;

	if (xq_nb_free(uq, ndescs) < ndescs)
		return -ENOSPC;

	for (i = 0; i < ndescs; i++) {
		u32 idx = uq->cached_prod++ & uq->mask;

		r[idx].addr = descs[i].addr;
		r[idx].len = descs[i].len;
	}

	u_smp_wmb();

	*uq->producer = uq->cached_prod;
	return 0;
}