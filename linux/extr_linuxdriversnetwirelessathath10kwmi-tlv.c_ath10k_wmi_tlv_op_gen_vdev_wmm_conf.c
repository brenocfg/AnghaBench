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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_wmm_params_all_arg {int /*<<< orphan*/  ac_vo; int /*<<< orphan*/  ac_vi; int /*<<< orphan*/  ac_bk; int /*<<< orphan*/  ac_be; } ;
struct wmi_tlv_vdev_set_wmm_cmd {TYPE_1__* vdev_wmm_params; int /*<<< orphan*/  vdev_id; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TLV_TAG_STRUCT_VDEV_SET_WMM_PARAMS_CMD ; 
 void* __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_wmi_set_wmm_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_vdev_wmm_conf(struct ath10k *ar, u32 vdev_id,
				    const struct wmi_wmm_params_all_arg *arg)
{
	struct wmi_tlv_vdev_set_wmm_cmd *cmd;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len;
	void *ptr;

	len = sizeof(*tlv) + sizeof(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SET_WMM_PARAMS_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[0].params, &arg->ac_be);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[1].params, &arg->ac_bk);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[2].params, &arg->ac_vi);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[3].params, &arg->ac_vo);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev wmm conf\n");
	return skb;
}