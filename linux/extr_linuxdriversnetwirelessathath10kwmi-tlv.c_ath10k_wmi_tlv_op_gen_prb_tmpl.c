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
struct wmi_tlv_prb_tmpl_cmd {void* buf_len; void* vdev_id; } ;
struct wmi_tlv_bcn_prb_info {scalar_t__ erp; scalar_t__ caps; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_ARRAY_BYTE ; 
 int WMI_TLV_TAG_STRUCT_BCN_PRB_INFO ; 
 int WMI_TLV_TAG_STRUCT_PRB_TMPL_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_prb_tmpl(struct ath10k *ar, u32 vdev_id,
			       struct sk_buff *prb)
{
	struct wmi_tlv_prb_tmpl_cmd *cmd;
	struct wmi_tlv_bcn_prb_info *info;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	void *ptr;
	size_t len;

	len = sizeof(*tlv) + sizeof(*cmd) +
	      sizeof(*tlv) + sizeof(*info) +
	      sizeof(*tlv) + roundup(prb->len, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PRB_TMPL_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->buf_len = __cpu_to_le32(prb->len);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_PRB_INFO);
	tlv->len = __cpu_to_le16(sizeof(*info));
	info = (void *)tlv->value;
	info->caps = 0;
	info->erp = 0;

	ptr += sizeof(*tlv);
	ptr += sizeof(*info);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(prb->len, 4));
	memcpy(tlv->value, prb->data, prb->len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv prb tmpl vdev_id %i\n",
		   vdev_id);
	return skb;
}