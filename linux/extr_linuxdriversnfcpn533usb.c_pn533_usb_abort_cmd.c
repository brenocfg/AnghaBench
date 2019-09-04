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
struct pn533_usb_phy {int /*<<< orphan*/  in_urb; } ;
struct pn533 {scalar_t__ device_type; struct pn533_usb_phy* phy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ PN533_DEVICE_ACR122U ; 
 int /*<<< orphan*/  pn533_usb_send_ack (struct pn533*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pn533_usb_abort_cmd(struct pn533 *dev, gfp_t flags)
{
	struct pn533_usb_phy *phy = dev->phy;

	/* ACR122U does not support any command which aborts last
	 * issued command i.e. as ACK for standard PN533. Additionally,
	 * it behaves stange, sending broken or incorrect responses,
	 * when we cancel urb before the chip will send response.
	 */
	if (dev->device_type == PN533_DEVICE_ACR122U)
		return;

	/* An ack will cancel the last issued command */
	pn533_usb_send_ack(dev, flags);

	/* cancel the urb request */
	usb_kill_urb(phy->in_urb);
}