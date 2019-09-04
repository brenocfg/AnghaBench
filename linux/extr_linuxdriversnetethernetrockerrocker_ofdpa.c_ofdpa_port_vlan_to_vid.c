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
struct ofdpa_port {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ ofdpa_vlan_id_is_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ofdpa_port_vlan_to_vid(const struct ofdpa_port *ofdpa_port,
				  __be16 vlan_id)
{
	if (ofdpa_vlan_id_is_internal(vlan_id))
		return 0;

	return ntohs(vlan_id);
}