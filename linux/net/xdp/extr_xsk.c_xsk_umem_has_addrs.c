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
struct xdp_umem {int /*<<< orphan*/  fq; } ;

/* Variables and functions */
 int xskq_has_addrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool xsk_umem_has_addrs(struct xdp_umem *umem, u32 cnt)
{
	return xskq_has_addrs(umem->fq, cnt);
}