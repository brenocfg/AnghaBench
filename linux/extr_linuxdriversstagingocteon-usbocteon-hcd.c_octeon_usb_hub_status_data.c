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
struct usb_hcd {int dummy; } ;
struct octeon_hcd {int /*<<< orphan*/  lock; } ;
struct cvmx_usb_port_status {int connect_change; } ;

/* Variables and functions */
 struct cvmx_usb_port_status cvmx_usb_get_status (struct octeon_hcd*) ; 
 struct octeon_hcd* hcd_to_octeon (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int octeon_usb_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct octeon_hcd *usb = hcd_to_octeon(hcd);
	struct cvmx_usb_port_status port_status;
	unsigned long flags;

	spin_lock_irqsave(&usb->lock, flags);
	port_status = cvmx_usb_get_status(usb);
	spin_unlock_irqrestore(&usb->lock, flags);
	buf[0] = port_status.connect_change << 1;

	return buf[0] != 0;
}