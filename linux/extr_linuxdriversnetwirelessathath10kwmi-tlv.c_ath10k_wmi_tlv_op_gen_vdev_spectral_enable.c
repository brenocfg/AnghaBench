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
struct wmi_vdev_spectral_enable_cmd {void* enable_cmd; void* trigger_cmd; void* vdev_id; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_STRUCT_VDEV_SPECTRAL_ENABLE_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_vdev_spectral_enable(struct ath10k *ar, u32 vdev_id,
					   u32 trigger, u32 enable)
{
	struct wmi_vdev_spectral_enable_cmd *cmd;
	struct sk_buff *skb;
	struct wmi_tlv *tlv;
	void *ptr;
	size_t len;

	len = sizeof(*tlv) + sizeof(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SPECTRAL_ENABLE_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->trigger_cmd = __cpu_to_le32(trigger);
	cmd->enable_cmd = __cpu_to_le32(enable);

	return skb;
}