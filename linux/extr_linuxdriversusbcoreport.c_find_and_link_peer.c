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
struct usb_port {scalar_t__ location; TYPE_2__* peer; } ;
struct usb_hub {struct usb_port** ports; struct usb_device* hdev; } ;
struct TYPE_3__ {struct usb_device* root_hub; } ;
struct usb_hcd {TYPE_1__ self; struct usb_hcd* shared_hcd; } ;
struct usb_device {int portnum; int maxchild; struct usb_device* parent; int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {struct usb_device* child; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_peers_report (struct usb_port*,struct usb_port*) ; 
 int /*<<< orphan*/  match_location ; 
 int /*<<< orphan*/  usb_for_each_dev (struct usb_port*,int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

__attribute__((used)) static void find_and_link_peer(struct usb_hub *hub, int port1)
{
	struct usb_port *port_dev = hub->ports[port1 - 1], *peer;
	struct usb_device *hdev = hub->hdev;
	struct usb_device *peer_hdev;
	struct usb_hub *peer_hub;

	/*
	 * If location data is available then we can only peer this port
	 * by a location match, not the default peer (lest we create a
	 * situation where we need to go back and undo a default peering
	 * when the port is later peered by location data)
	 */
	if (port_dev->location) {
		/* we link the peer in match_location() if found */
		usb_for_each_dev(port_dev, match_location);
		return;
	} else if (!hdev->parent) {
		struct usb_hcd *hcd = bus_to_hcd(hdev->bus);
		struct usb_hcd *peer_hcd = hcd->shared_hcd;

		if (!peer_hcd)
			return;

		peer_hdev = peer_hcd->self.root_hub;
	} else {
		struct usb_port *upstream;
		struct usb_device *parent = hdev->parent;
		struct usb_hub *parent_hub = usb_hub_to_struct_hub(parent);

		if (!parent_hub)
			return;

		upstream = parent_hub->ports[hdev->portnum - 1];
		if (!upstream || !upstream->peer)
			return;

		peer_hdev = upstream->peer->child;
	}

	peer_hub = usb_hub_to_struct_hub(peer_hdev);
	if (!peer_hub || port1 > peer_hdev->maxchild)
		return;

	/*
	 * we found a valid default peer, last check is to make sure it
	 * does not have location data
	 */
	peer = peer_hub->ports[port1 - 1];
	if (peer && peer->location == 0)
		link_peers_report(port_dev, peer);
}