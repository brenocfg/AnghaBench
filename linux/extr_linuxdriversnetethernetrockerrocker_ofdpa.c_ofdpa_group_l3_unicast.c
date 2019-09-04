#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int dummy; } ;
struct TYPE_2__ {int ttl_check; int /*<<< orphan*/  group_id; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; } ;
struct ofdpa_group_tbl_entry {TYPE_1__ l3_unicast; int /*<<< orphan*/  group_id; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ROCKER_GROUP_L2_INTERFACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKER_GROUP_L3_UNICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct ofdpa_group_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ofdpa_group_tbl_do (struct ofdpa_port*,int,struct ofdpa_group_tbl_entry*) ; 

__attribute__((used)) static int ofdpa_group_l3_unicast(struct ofdpa_port *ofdpa_port, int flags,
				  u32 index, const u8 *src_mac, const u8 *dst_mac,
				  __be16 vlan_id, bool ttl_check, u32 pport)
{
	struct ofdpa_group_tbl_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	entry->group_id = ROCKER_GROUP_L3_UNICAST(index);
	if (src_mac)
		ether_addr_copy(entry->l3_unicast.eth_src, src_mac);
	if (dst_mac)
		ether_addr_copy(entry->l3_unicast.eth_dst, dst_mac);
	entry->l3_unicast.vlan_id = vlan_id;
	entry->l3_unicast.ttl_check = ttl_check;
	entry->l3_unicast.group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, pport);

	return ofdpa_group_tbl_do(ofdpa_port, flags, entry);
}