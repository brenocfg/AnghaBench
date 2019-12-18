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
typedef  scalar_t__ u32 ;
struct ag71xx_ring {scalar_t__ curr; TYPE_2__* buf; } ;
struct ag71xx {struct ag71xx_ring rx_ring; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl; scalar_t__ data; } ;

/* Variables and functions */
 int AG71XX_RX_RING_SIZE ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 scalar_t__* NetRxPackets ; 
 int /*<<< orphan*/  PKTSIZE_ALIGN ; 
 int /*<<< orphan*/  flush_cache (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (scalar_t__) ; 

__attribute__((used)) static void ag71xx_ring_rx_clean(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	int i;

	if (!ring->buf)
		return;

	for (i = 0; i < AG71XX_RX_RING_SIZE; i++) {
	    ring->buf[i].desc->data = (u32) virt_to_phys(NetRxPackets[i]);
	    flush_cache((u32) NetRxPackets[i], PKTSIZE_ALIGN);
        ring->buf[i].desc->ctrl = DESC_EMPTY;
    }

	ring->curr = 0;
}