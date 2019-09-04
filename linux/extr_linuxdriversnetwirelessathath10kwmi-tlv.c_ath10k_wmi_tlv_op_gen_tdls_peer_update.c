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
typedef  int u32 ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct wmi_tdls_peer_update_cmd_arg {int vdev_id; int peer_state; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_tdls_peer_update_cmd {void* peer_state; TYPE_1__ peer_macaddr; void* vdev_id; } ;
struct wmi_tdls_peer_capab_arg {int peer_chan_len; int buff_sta_support; int off_chan_support; int peer_curr_operclass; int self_curr_operclass; int peer_operclass_len; int is_peer_responder; int pref_offchan_num; int pref_offchan_bw; int /*<<< orphan*/ * peer_operclass; int /*<<< orphan*/  peer_max_sp; int /*<<< orphan*/  peer_uapsd_queues; } ;
struct wmi_tdls_peer_capab {void* pref_offchan_bw; void* pref_offchan_num; void* is_peer_responder; int /*<<< orphan*/ * peer_operclass; void* peer_operclass_len; void* peer_chan_len; void* self_curr_operclass; void* peer_curr_operclass; void* off_chan_support; void* buff_sta_support; void* peer_qos; } ;
struct wmi_channel_arg {int dummy; } ;
struct wmi_channel {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int WMI_TDLS_MAX_SUPP_OPER_CLASSES ; 
 int WMI_TLV_TAG_ARRAY_STRUCT ; 
 int WMI_TLV_TAG_STRUCT_CHANNEL ; 
 int WMI_TLV_TAG_STRUCT_TDLS_PEER_CAPABILITIES ; 
 int WMI_TLV_TAG_STRUCT_TDLS_PEER_UPDATE_CMD ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_put_wmi_channel (struct wmi_channel*,struct wmi_channel_arg const*) ; 
 int ath10k_wmi_tlv_prepare_peer_qos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_tdls_peer_update(struct ath10k *ar,
				       const struct wmi_tdls_peer_update_cmd_arg *arg,
				       const struct wmi_tdls_peer_capab_arg *cap,
				       const struct wmi_channel_arg *chan_arg)
{
	struct wmi_tdls_peer_update_cmd *cmd;
	struct wmi_tdls_peer_capab *peer_cap;
	struct wmi_channel *chan;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	u32 peer_qos;
	void *ptr;
	int len;
	int i;

	len = sizeof(*tlv) + sizeof(*cmd) +
	      sizeof(*tlv) + sizeof(*peer_cap) +
	      sizeof(*tlv) + cap->peer_chan_len * sizeof(*chan);

	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_TDLS_PEER_UPDATE_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));

	cmd = (void *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);
	cmd->peer_state = __cpu_to_le32(arg->peer_state);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_TDLS_PEER_CAPABILITIES);
	tlv->len = __cpu_to_le16(sizeof(*peer_cap));
	peer_cap = (void *)tlv->value;
	peer_qos = ath10k_wmi_tlv_prepare_peer_qos(cap->peer_uapsd_queues,
						   cap->peer_max_sp);
	peer_cap->peer_qos = __cpu_to_le32(peer_qos);
	peer_cap->buff_sta_support = __cpu_to_le32(cap->buff_sta_support);
	peer_cap->off_chan_support = __cpu_to_le32(cap->off_chan_support);
	peer_cap->peer_curr_operclass = __cpu_to_le32(cap->peer_curr_operclass);
	peer_cap->self_curr_operclass = __cpu_to_le32(cap->self_curr_operclass);
	peer_cap->peer_chan_len = __cpu_to_le32(cap->peer_chan_len);
	peer_cap->peer_operclass_len = __cpu_to_le32(cap->peer_operclass_len);

	for (i = 0; i < WMI_TDLS_MAX_SUPP_OPER_CLASSES; i++)
		peer_cap->peer_operclass[i] = cap->peer_operclass[i];

	peer_cap->is_peer_responder = __cpu_to_le32(cap->is_peer_responder);
	peer_cap->pref_offchan_num = __cpu_to_le32(cap->pref_offchan_num);
	peer_cap->pref_offchan_bw = __cpu_to_le32(cap->pref_offchan_bw);

	ptr += sizeof(*tlv);
	ptr += sizeof(*peer_cap);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(cap->peer_chan_len * sizeof(*chan));

	ptr += sizeof(*tlv);

	for (i = 0; i < cap->peer_chan_len; i++) {
		tlv = ptr;
		tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
		tlv->len = __cpu_to_le16(sizeof(*chan));
		chan = (void *)tlv->value;
		ath10k_wmi_put_wmi_channel(chan, &chan_arg[i]);

		ptr += sizeof(*tlv);
		ptr += sizeof(*chan);
	}

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv tdls peer update vdev %i state %d n_chans %u\n",
		   arg->vdev_id, arg->peer_state, cap->peer_chan_len);
	return skb;
}