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
struct xdp_umem_uqueue {size_t mask; scalar_t__ cached_prod; scalar_t__* producer; int /*<<< orphan*/ * ring; } ;
struct xdp_desc {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  u_smp_wmb () ; 
 size_t umem_nb_free (struct xdp_umem_uqueue*,size_t) ; 

__attribute__((used)) static inline int umem_fill_to_kernel_ex(struct xdp_umem_uqueue *fq,
					 struct xdp_desc *d,
					 size_t nb)
{
	u32 i;

	if (umem_nb_free(fq, nb) < nb)
		return -ENOSPC;

	for (i = 0; i < nb; i++) {
		u32 idx = fq->cached_prod++ & fq->mask;

		fq->ring[idx] = d[i].addr;
	}

	u_smp_wmb();

	*fq->producer = fq->cached_prod;

	return 0;
}