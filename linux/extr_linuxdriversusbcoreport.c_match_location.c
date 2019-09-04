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
struct TYPE_4__ {TYPE_1__* parent; } ;
struct usb_port {scalar_t__ location; TYPE_2__ dev; } ;
struct usb_hub {struct usb_port** ports; } ;
struct usb_hcd {struct usb_hcd* shared_hcd; } ;
struct usb_device {int maxchild; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_peers_report (struct usb_port*,struct usb_port*) ; 
 struct usb_device* to_usb_device (int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

__attribute__((used)) static int match_location(struct usb_device *peer_hdev, void *p)
{
	int port1;
	struct usb_hcd *hcd, *peer_hcd;
	struct usb_port *port_dev = p, *peer;
	struct usb_hub *peer_hub = usb_hub_to_struct_hub(peer_hdev);
	struct usb_device *hdev = to_usb_device(port_dev->dev.parent->parent);

	if (!peer_hub)
		return 0;

	hcd = bus_to_hcd(hdev->bus);
	peer_hcd = bus_to_hcd(peer_hdev->bus);
	/* peer_hcd is provisional until we verify it against the known peer */
	if (peer_hcd != hcd->shared_hcd)
		return 0;

	for (port1 = 1; port1 <= peer_hdev->maxchild; port1++) {
		peer = peer_hub->ports[port1 - 1];
		if (peer && peer->location == port_dev->location) {
			link_peers_report(port_dev, peer);
			return 1; /* done */
		}
	}

	return 0;
}