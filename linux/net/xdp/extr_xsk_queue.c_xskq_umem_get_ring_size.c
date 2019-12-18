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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct xsk_queue {int nentries; } ;
struct xdp_umem_ring {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 xskq_umem_get_ring_size(struct xsk_queue *q)
{
	return sizeof(struct xdp_umem_ring) + q->nentries * sizeof(u64);
}