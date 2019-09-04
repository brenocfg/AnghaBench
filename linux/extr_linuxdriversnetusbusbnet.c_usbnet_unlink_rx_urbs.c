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
struct usbnet {int /*<<< orphan*/  bh; int /*<<< orphan*/  rxq; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_urbs (struct usbnet*,int /*<<< orphan*/ *) ; 

void usbnet_unlink_rx_urbs(struct usbnet *dev)
{
	if (netif_running(dev->net)) {
		(void) unlink_urbs (dev, &dev->rxq);
		tasklet_schedule(&dev->bh);
	}
}