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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t __get_vlan_tinfo_size(void)
{
	return nla_total_size(0) + /* nest IFLA_BRIDGE_VLAN_TUNNEL_INFO */
		  nla_total_size(sizeof(u32)) + /* IFLA_BRIDGE_VLAN_TUNNEL_ID */
		  nla_total_size(sizeof(u16)) + /* IFLA_BRIDGE_VLAN_TUNNEL_VID */
		  nla_total_size(sizeof(u16)); /* IFLA_BRIDGE_VLAN_TUNNEL_FLAGS */
}