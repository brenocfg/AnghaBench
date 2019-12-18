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
struct xdp_umem {int /*<<< orphan*/  fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  xskq_discard_addr (int /*<<< orphan*/ ) ; 

void xsk_umem_discard_addr(struct xdp_umem *umem)
{
	xskq_discard_addr(umem->fq);
}