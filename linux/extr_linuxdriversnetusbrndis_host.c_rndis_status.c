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
struct usbnet {int /*<<< orphan*/  net; } ;
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rndis_status(struct usbnet *dev, struct urb *urb)
{
	netdev_dbg(dev->net, "rndis status urb, len %d stat %d\n",
		   urb->actual_length, urb->status);
	// FIXME for keepalives, respond immediately (asynchronously)
	// if not an RNDIS status, do like cdc_status(dev,urb) does
}