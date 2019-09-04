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
struct rocker_tlv {int dummy; } ;
struct rocker_port {int /*<<< orphan*/  dev; } ;
struct rocker {unsigned int port_count; struct rocker_port** ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t ROCKER_TLV_EVENT_LINK_CHANGED_LINKUP ; 
 int /*<<< orphan*/  ROCKER_TLV_EVENT_LINK_CHANGED_MAX ; 
 size_t ROCKER_TLV_EVENT_LINK_CHANGED_PPORT ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_port_link_down (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_port_link_up (struct rocker_port*) ; 
 int rocker_tlv_get_u32 (struct rocker_tlv const*) ; 
 int rocker_tlv_get_u8 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_nested (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_tlv const*) ; 

__attribute__((used)) static int rocker_event_link_change(const struct rocker *rocker,
				    const struct rocker_tlv *info)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_EVENT_LINK_CHANGED_MAX + 1];
	unsigned int port_number;
	bool link_up;
	struct rocker_port *rocker_port;

	rocker_tlv_parse_nested(attrs, ROCKER_TLV_EVENT_LINK_CHANGED_MAX, info);
	if (!attrs[ROCKER_TLV_EVENT_LINK_CHANGED_PPORT] ||
	    !attrs[ROCKER_TLV_EVENT_LINK_CHANGED_LINKUP])
		return -EIO;
	port_number =
		rocker_tlv_get_u32(attrs[ROCKER_TLV_EVENT_LINK_CHANGED_PPORT]) - 1;
	link_up = rocker_tlv_get_u8(attrs[ROCKER_TLV_EVENT_LINK_CHANGED_LINKUP]);

	if (port_number >= rocker->port_count)
		return -EINVAL;

	rocker_port = rocker->ports[port_number];
	if (netif_carrier_ok(rocker_port->dev) != link_up) {
		if (link_up)
			rocker_port_link_up(rocker_port);
		else
			rocker_port_link_down(rocker_port);
	}

	return 0;
}