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
struct xdp_umem {scalar_t__ cq; scalar_t__ fq; } ;

/* Variables and functions */

bool xdp_umem_validate_queues(struct xdp_umem *umem)
{
	return umem->fq && umem->cq;
}