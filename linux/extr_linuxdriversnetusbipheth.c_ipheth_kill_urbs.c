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
struct ipheth_device {int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipheth_kill_urbs(struct ipheth_device *dev)
{
	usb_kill_urb(dev->tx_urb);
	usb_kill_urb(dev->rx_urb);
}