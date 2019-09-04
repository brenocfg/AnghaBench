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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct ofdpa_port {int dummy; } ;
struct TYPE_3__ {int has_eth_dst; int has_eth_dst_mask; int goto_tbl; int copy_to_cpu; void* group_id; void* tunnel_id; scalar_t__ vlan_id; int /*<<< orphan*/  eth_dst_mask; int /*<<< orphan*/  eth_dst; } ;
struct TYPE_4__ {TYPE_1__ bridge; void* priority; int /*<<< orphan*/  tbl_id; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* OFDPA_PRIORITY_BRIDGING_TENANT ; 
 void* OFDPA_PRIORITY_BRIDGING_TENANT_DFLT_EXACT ; 
 void* OFDPA_PRIORITY_BRIDGING_TENANT_DFLT_WILD ; 
 void* OFDPA_PRIORITY_BRIDGING_VLAN ; 
 void* OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_EXACT ; 
 void* OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_WILD ; 
 void* OFDPA_PRIORITY_UNKNOWN ; 
 int /*<<< orphan*/  ROCKER_OF_DPA_TABLE_ID_BRIDGING ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mac ; 
 struct ofdpa_flow_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_do (struct ofdpa_port*,int,struct ofdpa_flow_tbl_entry*) ; 

__attribute__((used)) static int ofdpa_flow_tbl_bridge(struct ofdpa_port *ofdpa_port,
				 int flags, const u8 *eth_dst,
				 const u8 *eth_dst_mask,  __be16 vlan_id,
				 u32 tunnel_id,
				 enum rocker_of_dpa_table_id goto_tbl,
				 u32 group_id, bool copy_to_cpu)
{
	struct ofdpa_flow_tbl_entry *entry;
	u32 priority;
	bool vlan_bridging = !!vlan_id;
	bool dflt = !eth_dst || (eth_dst && eth_dst_mask);
	bool wild = false;

	entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return -ENOMEM;

	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_BRIDGING;

	if (eth_dst) {
		entry->key.bridge.has_eth_dst = 1;
		ether_addr_copy(entry->key.bridge.eth_dst, eth_dst);
	}
	if (eth_dst_mask) {
		entry->key.bridge.has_eth_dst_mask = 1;
		ether_addr_copy(entry->key.bridge.eth_dst_mask, eth_dst_mask);
		if (!ether_addr_equal(eth_dst_mask, ff_mac))
			wild = true;
	}

	priority = OFDPA_PRIORITY_UNKNOWN;
	if (vlan_bridging && dflt && wild)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_WILD;
	else if (vlan_bridging && dflt && !wild)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_EXACT;
	else if (vlan_bridging && !dflt)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN;
	else if (!vlan_bridging && dflt && wild)
		priority = OFDPA_PRIORITY_BRIDGING_TENANT_DFLT_WILD;
	else if (!vlan_bridging && dflt && !wild)
		priority = OFDPA_PRIORITY_BRIDGING_TENANT_DFLT_EXACT;
	else if (!vlan_bridging && !dflt)
		priority = OFDPA_PRIORITY_BRIDGING_TENANT;

	entry->key.priority = priority;
	entry->key.bridge.vlan_id = vlan_id;
	entry->key.bridge.tunnel_id = tunnel_id;
	entry->key.bridge.goto_tbl = goto_tbl;
	entry->key.bridge.group_id = group_id;
	entry->key.bridge.copy_to_cpu = copy_to_cpu;

	return ofdpa_flow_tbl_do(ofdpa_port, flags, entry);
}