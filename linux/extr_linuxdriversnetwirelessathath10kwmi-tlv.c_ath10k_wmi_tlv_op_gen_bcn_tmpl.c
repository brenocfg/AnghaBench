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
typedef  size_t u32 ;
struct wmi_tlv_bcn_tmpl_cmd {void* buf_len; void* tim_ie_offset; void* vdev_id; } ;
struct wmi_tlv_bcn_prb_info {scalar_t__ ies; void* erp; void* caps; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {size_t len; void* data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int WMI_TLV_TAG_ARRAY_BYTE ; 
 int WMI_TLV_TAG_STRUCT_BCN_PRB_INFO ; 
 int WMI_TLV_TAG_STRUCT_BCN_TMPL_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,size_t) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int roundup (size_t,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_bcn_tmpl(struct ath10k *ar, u32 vdev_id,
			       u32 tim_ie_offset, struct sk_buff *bcn,
			       u32 prb_caps, u32 prb_erp, void *prb_ies,
			       size_t prb_ies_len)
{
	struct wmi_tlv_bcn_tmpl_cmd *cmd;
	struct wmi_tlv_bcn_prb_info *info;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	void *ptr;
	size_t len;

	if (WARN_ON(prb_ies_len > 0 && !prb_ies))
		return ERR_PTR(-EINVAL);

	len = sizeof(*tlv) + sizeof(*cmd) +
	      sizeof(*tlv) + sizeof(*info) + prb_ies_len +
	      sizeof(*tlv) + roundup(bcn->len, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_TMPL_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->tim_ie_offset = __cpu_to_le32(tim_ie_offset);
	cmd->buf_len = __cpu_to_le32(bcn->len);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	/* FIXME: prb_ies_len should be probably aligned to 4byte boundary but
	 * then it is then impossible to pass original ie len.
	 * This chunk is not used yet so if setting probe resp template yields
	 * problems with beaconing or crashes firmware look here.
	 */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_PRB_INFO);
	tlv->len = __cpu_to_le16(sizeof(*info) + prb_ies_len);
	info = (void *)tlv->value;
	info->caps = __cpu_to_le32(prb_caps);
	info->erp = __cpu_to_le32(prb_erp);
	memcpy(info->ies, prb_ies, prb_ies_len);

	ptr += sizeof(*tlv);
	ptr += sizeof(*info);
	ptr += prb_ies_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(bcn->len, 4));
	memcpy(tlv->value, bcn->data, bcn->len);

	/* FIXME: Adjust TSF? */

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv bcn tmpl vdev_id %i\n",
		   vdev_id);
	return skb;
}