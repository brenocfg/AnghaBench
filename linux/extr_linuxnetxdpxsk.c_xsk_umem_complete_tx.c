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
typedef  int /*<<< orphan*/  u32 ;
struct xdp_umem {int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  xskq_produce_flush_addr_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xsk_umem_complete_tx(struct xdp_umem *umem, u32 nb_entries)
{
	xskq_produce_flush_addr_n(umem->cq, nb_entries);
}