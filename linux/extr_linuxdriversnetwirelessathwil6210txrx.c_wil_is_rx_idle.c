#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wil_ring {size_t swhead; TYPE_2__* va; } ;
struct wil6210_priv {struct wil_ring ring_rx; } ;
struct TYPE_6__ {int status; } ;
struct vring_rx_desc {TYPE_3__ dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  legacy; } ;
struct TYPE_5__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int RX_DMA_STATUS_DU ; 

__attribute__((used)) static bool wil_is_rx_idle(struct wil6210_priv *wil)
{
	struct vring_rx_desc *_d;
	struct wil_ring *ring = &wil->ring_rx;

	_d = (struct vring_rx_desc *)&ring->va[ring->swhead].rx.legacy;
	if (_d->dma.status & RX_DMA_STATUS_DU)
		return false;

	return true;
}