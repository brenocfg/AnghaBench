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
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int dummy; } ;
struct TYPE_3__ {int goto_tbl; int untagged; void* new_vlan_id; void* vlan_id_mask; void* vlan_id; int /*<<< orphan*/  in_pport; } ;
struct TYPE_4__ {TYPE_1__ vlan; int /*<<< orphan*/  tbl_id; int /*<<< orphan*/  priority; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  void* __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OFDPA_PRIORITY_VLAN ; 
 int /*<<< orphan*/  ROCKER_OF_DPA_TABLE_ID_VLAN ; 
 struct ofdpa_flow_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_do (struct ofdpa_port*,int,struct ofdpa_flow_tbl_entry*) ; 

__attribute__((used)) static int ofdpa_flow_tbl_vlan(struct ofdpa_port *ofdpa_port,
			       int flags,
			       u32 in_pport, __be16 vlan_id,
			       __be16 vlan_id_mask,
			       enum rocker_of_dpa_table_id goto_tbl,
			       bool untagged, __be16 new_vlan_id)
{
	struct ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	entry->key.priority = OFDPA_PRIORITY_VLAN;
	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_VLAN;
	entry->key.vlan.in_pport = in_pport;
	entry->key.vlan.vlan_id = vlan_id;
	entry->key.vlan.vlan_id_mask = vlan_id_mask;
	entry->key.vlan.goto_tbl = goto_tbl;

	entry->key.vlan.untagged = untagged;
	entry->key.vlan.new_vlan_id = new_vlan_id;

	return ofdpa_flow_tbl_do(ofdpa_port, flags, entry);
}