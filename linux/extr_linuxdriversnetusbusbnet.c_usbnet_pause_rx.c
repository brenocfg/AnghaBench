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
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_PAUSED ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void usbnet_pause_rx(struct usbnet *dev)
{
	set_bit(EVENT_RX_PAUSED, &dev->flags);

	netif_dbg(dev, rx_status, dev->net, "paused rx queue enabled\n");
}