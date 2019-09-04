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
struct rocker_port {int dummy; } ;
struct rocker {unsigned int port_count; struct rocker_port** ports; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t ROCKER_TLV_EVENT_MAC_VLAN_MAC ; 
 int /*<<< orphan*/  ROCKER_TLV_EVENT_MAC_VLAN_MAX ; 
 size_t ROCKER_TLV_EVENT_MAC_VLAN_PPORT ; 
 size_t ROCKER_TLV_EVENT_MAC_VLAN_VLAN_ID ; 
 unsigned char* rocker_tlv_data (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_get_be16 (struct rocker_tlv const*) ; 
 int rocker_tlv_get_u32 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_nested (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_tlv const*) ; 
 int rocker_world_port_ev_mac_vlan_seen (struct rocker_port*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_event_mac_vlan_seen(const struct rocker *rocker,
				      const struct rocker_tlv *info)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAX + 1];
	unsigned int port_number;
	struct rocker_port *rocker_port;
	const unsigned char *addr;
	__be16 vlan_id;

	rocker_tlv_parse_nested(attrs, ROCKER_TLV_EVENT_MAC_VLAN_MAX, info);
	if (!attrs[ROCKER_TLV_EVENT_MAC_VLAN_PPORT] ||
	    !attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAC] ||
	    !attrs[ROCKER_TLV_EVENT_MAC_VLAN_VLAN_ID])
		return -EIO;
	port_number =
		rocker_tlv_get_u32(attrs[ROCKER_TLV_EVENT_MAC_VLAN_PPORT]) - 1;
	addr = rocker_tlv_data(attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAC]);
	vlan_id = rocker_tlv_get_be16(attrs[ROCKER_TLV_EVENT_MAC_VLAN_VLAN_ID]);

	if (port_number >= rocker->port_count)
		return -EINVAL;

	rocker_port = rocker->ports[port_number];
	return rocker_world_port_ev_mac_vlan_seen(rocker_port, addr, vlan_id);
}