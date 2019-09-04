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
struct xdp_uqueue {unsigned int mask; scalar_t__ cached_cons; scalar_t__* consumer; struct xdp_desc* ring; } ;
struct xdp_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  u_smp_rmb () ; 
 int /*<<< orphan*/  u_smp_wmb () ; 
 int xq_nb_avail (struct xdp_uqueue*,int) ; 

__attribute__((used)) static inline int xq_deq(struct xdp_uqueue *uq,
			 struct xdp_desc *descs,
			 int ndescs)
{
	struct xdp_desc *r = uq->ring;
	unsigned int idx;
	int i, entries;

	entries = xq_nb_avail(uq, ndescs);

	u_smp_rmb();

	for (i = 0; i < entries; i++) {
		idx = uq->cached_cons++ & uq->mask;
		descs[i] = r[idx];
	}

	if (entries > 0) {
		u_smp_wmb();

		*uq->consumer = uq->cached_cons;
	}

	return entries;
}