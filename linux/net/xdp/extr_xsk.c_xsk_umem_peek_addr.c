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
struct xdp_umem {int /*<<< orphan*/  fq; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xskq_peek_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xdp_umem*) ; 

u64 *xsk_umem_peek_addr(struct xdp_umem *umem, u64 *addr)
{
	return xskq_peek_addr(umem->fq, addr, umem);
}