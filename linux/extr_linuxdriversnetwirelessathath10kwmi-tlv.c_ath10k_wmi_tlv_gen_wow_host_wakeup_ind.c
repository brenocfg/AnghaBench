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
struct wmi_tlv_wow_host_wakeup_ind {int dummy; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_STRUCT_WOW_HOSTWAKEUP_FROM_SLEEP_CMD ; 
 void* __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_gen_wow_host_wakeup_ind(struct ath10k *ar)
{
	struct wmi_tlv_wow_host_wakeup_ind *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len;

	len = sizeof(*tlv) + sizeof(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	tlv = (struct wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_HOSTWAKEUP_FROM_SLEEP_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow host wakeup ind\n");
	return skb;
}