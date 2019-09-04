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
struct b43_pio {int dummy; } ;
struct b43_wldev {struct b43_pio pio; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_using_pio_transfers (struct b43_wldev*) ; 
 int /*<<< orphan*/  destroy_queue_rx (struct b43_pio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_queue_tx (struct b43_pio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_queue ; 
 int /*<<< orphan*/  tx_queue_AC_BE ; 
 int /*<<< orphan*/  tx_queue_AC_BK ; 
 int /*<<< orphan*/  tx_queue_AC_VI ; 
 int /*<<< orphan*/  tx_queue_AC_VO ; 
 int /*<<< orphan*/  tx_queue_mcast ; 

void b43_pio_free(struct b43_wldev *dev)
{
	struct b43_pio *pio;

	if (!b43_using_pio_transfers(dev))
		return;
	pio = &dev->pio;

	destroy_queue_rx(pio, rx_queue);
	destroy_queue_tx(pio, tx_queue_mcast);
	destroy_queue_tx(pio, tx_queue_AC_VO);
	destroy_queue_tx(pio, tx_queue_AC_VI);
	destroy_queue_tx(pio, tx_queue_AC_BE);
	destroy_queue_tx(pio, tx_queue_AC_BK);
}