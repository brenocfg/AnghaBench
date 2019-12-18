#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdp_umem {int need_wakeup; TYPE_2__* fq; } ;
struct TYPE_4__ {TYPE_1__* ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDP_RING_NEED_WAKEUP ; 
 int XDP_WAKEUP_RX ; 

void xsk_set_rx_need_wakeup(struct xdp_umem *umem)
{
	if (umem->need_wakeup & XDP_WAKEUP_RX)
		return;

	umem->fq->ring->flags |= XDP_RING_NEED_WAKEUP;
	umem->need_wakeup |= XDP_WAKEUP_RX;
}