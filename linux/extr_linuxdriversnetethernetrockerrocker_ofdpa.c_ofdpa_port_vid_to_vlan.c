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
typedef  int /*<<< orphan*/  u16 ;
struct ofdpa_port {scalar_t__ internal_vlan_id; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 ofdpa_port_vid_to_vlan(const struct ofdpa_port *ofdpa_port,
				     u16 vid, bool *pop_vlan)
{
	__be16 vlan_id;

	if (pop_vlan)
		*pop_vlan = false;
	vlan_id = htons(vid);
	if (!vlan_id) {
		vlan_id = ofdpa_port->internal_vlan_id;
		if (pop_vlan)
			*pop_vlan = true;
	}

	return vlan_id;
}