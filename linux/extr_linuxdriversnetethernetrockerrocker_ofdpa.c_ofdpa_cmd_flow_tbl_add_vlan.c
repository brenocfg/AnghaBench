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
struct rocker_desc_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  new_vlan_id; scalar_t__ untagged; int /*<<< orphan*/  goto_tbl; int /*<<< orphan*/  vlan_id_mask; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  in_pport; } ;
struct TYPE_4__ {TYPE_1__ vlan; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GOTO_TABLE_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_IN_PPORT ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_NEW_VLAN_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_VLAN_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_VLAN_ID_MASK ; 
 scalar_t__ rocker_tlv_put_be16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofdpa_cmd_flow_tbl_add_vlan(struct rocker_desc_info *desc_info,
			    const struct ofdpa_flow_tbl_entry *entry)
{
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.vlan.in_pport))
		return -EMSGSIZE;
	if (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.vlan.vlan_id))
		return -EMSGSIZE;
	if (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID_MASK,
				entry->key.vlan.vlan_id_mask))
		return -EMSGSIZE;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.vlan.goto_tbl))
		return -EMSGSIZE;
	if (entry->key.vlan.untagged &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_NEW_VLAN_ID,
				entry->key.vlan.new_vlan_id))
		return -EMSGSIZE;

	return 0;
}