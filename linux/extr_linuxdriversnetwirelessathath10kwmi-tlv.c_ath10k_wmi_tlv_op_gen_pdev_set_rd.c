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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_tlv_pdev_set_rd_cmd {void* conform_limit_5ghz; void* conform_limit_2ghz; void* regd_5ghz; void* regd_2ghz; void* regd; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_dfs_region { ____Placeholder_wmi_dfs_region } wmi_dfs_region ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_STRUCT_PDEV_SET_REGDOMAIN_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_pdev_set_rd(struct ath10k *ar,
				  u16 rd, u16 rd2g, u16 rd5g,
				  u16 ctl2g, u16 ctl5g,
				  enum wmi_dfs_region dfs_reg)
{
	struct wmi_tlv_pdev_set_rd_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*tlv) + sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	tlv = (void *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SET_REGDOMAIN_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->regd = __cpu_to_le32(rd);
	cmd->regd_2ghz = __cpu_to_le32(rd2g);
	cmd->regd_5ghz = __cpu_to_le32(rd5g);
	cmd->conform_limit_2ghz = __cpu_to_le32(ctl2g);
	cmd->conform_limit_5ghz = __cpu_to_le32(ctl5g);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev set rd\n");
	return skb;
}