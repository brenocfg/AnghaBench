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
struct TYPE_3__ {scalar_t__ copy_to_cpu; scalar_t__ group_id; int /*<<< orphan*/  goto_tbl; scalar_t__ tunnel_id; scalar_t__ vlan_id; int /*<<< orphan*/  eth_dst_mask; scalar_t__ has_eth_dst_mask; int /*<<< orphan*/  eth_dst; scalar_t__ has_eth_dst; } ;
struct TYPE_4__ {TYPE_1__ bridge; } ;
struct ofdpa_flow_tbl_entry {TYPE_2__ key; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_COPY_CPU_ACTION ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_DST_MAC ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_DST_MAC_MASK ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GOTO_TABLE_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_GROUP_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_TUNNEL_ID ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_VLAN_ID ; 
 scalar_t__ rocker_tlv_put (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_be16 (struct rocker_desc_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rocker_tlv_put_u8 (struct rocker_desc_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ofdpa_cmd_flow_tbl_add_bridge(struct rocker_desc_info *desc_info,
			      const struct ofdpa_flow_tbl_entry *entry)
{
	if (entry->key.bridge.has_eth_dst &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->key.bridge.eth_dst))
		return -EMSGSIZE;
	if (entry->key.bridge.has_eth_dst_mask &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC_MASK,
			   ETH_ALEN, entry->key.bridge.eth_dst_mask))
		return -EMSGSIZE;
	if (entry->key.bridge.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.bridge.vlan_id))
		return -EMSGSIZE;
	if (entry->key.bridge.tunnel_id &&
	    rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_TUNNEL_ID,
			       entry->key.bridge.tunnel_id))
		return -EMSGSIZE;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.bridge.goto_tbl))
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->key.bridge.group_id))
		return -EMSGSIZE;
	if (entry->key.bridge.copy_to_cpu &&
	    rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_COPY_CPU_ACTION,
			      entry->key.bridge.copy_to_cpu))
		return -EMSGSIZE;

	return 0;
}