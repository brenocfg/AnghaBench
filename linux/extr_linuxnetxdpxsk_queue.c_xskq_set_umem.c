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
struct xdp_umem_props {int dummy; } ;
struct xsk_queue {struct xdp_umem_props umem_props; } ;

/* Variables and functions */

void xskq_set_umem(struct xsk_queue *q, struct xdp_umem_props *umem_props)
{
	if (!q)
		return;

	q->umem_props = *umem_props;
}