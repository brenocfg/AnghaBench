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
typedef  enum udp_parsable_tunnel_type { ____Placeholder_udp_parsable_tunnel_type } udp_parsable_tunnel_type ;

/* Variables and functions */
 int TUNNEL_ENCAP_UDP_PORT_ENTRY_GENEVE ; 
 int TUNNEL_ENCAP_UDP_PORT_ENTRY_VXLAN ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 

__attribute__((used)) static int efx_udp_tunnel_type_map(enum udp_parsable_tunnel_type in)
{
	switch (in) {
	case UDP_TUNNEL_TYPE_VXLAN:
		return TUNNEL_ENCAP_UDP_PORT_ENTRY_VXLAN;
	case UDP_TUNNEL_TYPE_GENEVE:
		return TUNNEL_ENCAP_UDP_PORT_ENTRY_GENEVE;
	default:
		return -1;
	}
}