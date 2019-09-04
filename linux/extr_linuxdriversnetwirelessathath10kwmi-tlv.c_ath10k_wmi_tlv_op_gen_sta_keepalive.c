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
struct wmi_tlv_sta_keepalive_cmd {void* interval; void* method; void* enabled; void* vdev_id; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_sta_keepalive_arp_resp {TYPE_1__ dest_mac_addr; int /*<<< orphan*/  dest_ip4_addr; int /*<<< orphan*/  src_ip4_addr; } ;
struct wmi_sta_keepalive_arg {int /*<<< orphan*/  interval; int /*<<< orphan*/  method; int /*<<< orphan*/  enabled; int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  dest_mac_addr; int /*<<< orphan*/  dest_ip4_addr; int /*<<< orphan*/  src_ip4_addr; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_STRUCT_STA_KEEPALIVE_CMD ; 
 int WMI_TLV_TAG_STRUCT_STA_KEEPALVE_ARP_RESPONSE ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_sta_keepalive(struct ath10k *ar,
				    const struct wmi_sta_keepalive_arg *arg)
{
	struct wmi_tlv_sta_keepalive_cmd *cmd;
	struct wmi_sta_keepalive_arp_resp *arp;
	struct sk_buff *skb;
	struct wmi_tlv *tlv;
	void *ptr;
	size_t len;

	len = sizeof(*tlv) + sizeof(*cmd) +
	      sizeof(*tlv) + sizeof(*arp);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_KEEPALIVE_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->enabled = __cpu_to_le32(arg->enabled);
	cmd->method = __cpu_to_le32(arg->method);
	cmd->interval = __cpu_to_le32(arg->interval);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_KEEPALVE_ARP_RESPONSE);
	tlv->len = __cpu_to_le16(sizeof(*arp));
	arp = (void *)tlv->value;

	arp->src_ip4_addr = arg->src_ip4_addr;
	arp->dest_ip4_addr = arg->dest_ip4_addr;
	ether_addr_copy(arp->dest_mac_addr.addr, arg->dest_mac_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv sta keepalive vdev %d enabled %d method %d interval %d\n",
		   arg->vdev_id, arg->enabled, arg->method, arg->interval);
	return skb;
}