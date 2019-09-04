#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wmi_vht_rate_set {void* tx_mcs_set; void* tx_max_rate; void* rx_mcs_set; void* rx_max_rate; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct wmi_tlv_peer_assoc_cmd {TYPE_1__ mac_addr; void* num_ht_rates; void* num_legacy_rates; void* phy_mode; void* vht_caps; void* nss; void* rate_caps; void* mpdu_density; void* max_mpdu; void* ht_caps; void* listen_intval; void* caps; void* flags; void* assoc_id; void* new_assoc; void* vdev_id; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct TYPE_8__ {int rx_max_rate; int rx_mcs_set; int tx_max_rate; int tx_mcs_set; } ;
struct TYPE_7__ {int num_rates; int /*<<< orphan*/  rates; } ;
struct TYPE_6__ {int num_rates; int /*<<< orphan*/  rates; } ;
struct wmi_peer_assoc_complete_arg {int peer_mpdu_density; int vdev_id; int peer_aid; int peer_flags; int peer_caps; int peer_listen_intval; int peer_ht_caps; int peer_max_mpdu; int peer_rate_caps; int peer_num_spatial_streams; int peer_vht_caps; int peer_phymode; TYPE_4__ peer_vht_rates; TYPE_3__ peer_ht_rates; TYPE_2__ peer_legacy_rates; int /*<<< orphan*/  addr; scalar_t__ peer_reassoc; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MAX_SUPPORTED_RATES ; 
 int WMI_TLV_TAG_ARRAY_BYTE ; 
 int WMI_TLV_TAG_STRUCT_PEER_ASSOC_COMPLETE_CMD ; 
 int WMI_TLV_TAG_STRUCT_VHT_RATE_SET ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 size_t roundup (int,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_peer_assoc(struct ath10k *ar,
				 const struct wmi_peer_assoc_complete_arg *arg)
{
	struct wmi_tlv_peer_assoc_cmd *cmd;
	struct wmi_vht_rate_set *vht_rate;
	struct wmi_tlv *tlv;
	struct sk_buff *skb;
	size_t len, legacy_rate_len, ht_rate_len;
	void *ptr;

	if (arg->peer_mpdu_density > 16)
		return ERR_PTR(-EINVAL);
	if (arg->peer_legacy_rates.num_rates > MAX_SUPPORTED_RATES)
		return ERR_PTR(-EINVAL);
	if (arg->peer_ht_rates.num_rates > MAX_SUPPORTED_RATES)
		return ERR_PTR(-EINVAL);

	legacy_rate_len = roundup(arg->peer_legacy_rates.num_rates,
				  sizeof(__le32));
	ht_rate_len = roundup(arg->peer_ht_rates.num_rates, sizeof(__le32));
	len = (sizeof(*tlv) + sizeof(*cmd)) +
	      (sizeof(*tlv) + legacy_rate_len) +
	      (sizeof(*tlv) + ht_rate_len) +
	      (sizeof(*tlv) + sizeof(*vht_rate));
	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = (void *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_ASSOC_COMPLETE_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->new_assoc = __cpu_to_le32(arg->peer_reassoc ? 0 : 1);
	cmd->assoc_id = __cpu_to_le32(arg->peer_aid);
	cmd->flags = __cpu_to_le32(arg->peer_flags);
	cmd->caps = __cpu_to_le32(arg->peer_caps);
	cmd->listen_intval = __cpu_to_le32(arg->peer_listen_intval);
	cmd->ht_caps = __cpu_to_le32(arg->peer_ht_caps);
	cmd->max_mpdu = __cpu_to_le32(arg->peer_max_mpdu);
	cmd->mpdu_density = __cpu_to_le32(arg->peer_mpdu_density);
	cmd->rate_caps = __cpu_to_le32(arg->peer_rate_caps);
	cmd->nss = __cpu_to_le32(arg->peer_num_spatial_streams);
	cmd->vht_caps = __cpu_to_le32(arg->peer_vht_caps);
	cmd->phy_mode = __cpu_to_le32(arg->peer_phymode);
	cmd->num_legacy_rates = __cpu_to_le32(arg->peer_legacy_rates.num_rates);
	cmd->num_ht_rates = __cpu_to_le32(arg->peer_ht_rates.num_rates);
	ether_addr_copy(cmd->mac_addr.addr, arg->addr);

	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(legacy_rate_len);
	memcpy(tlv->value, arg->peer_legacy_rates.rates,
	       arg->peer_legacy_rates.num_rates);

	ptr += sizeof(*tlv);
	ptr += legacy_rate_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(ht_rate_len);
	memcpy(tlv->value, arg->peer_ht_rates.rates,
	       arg->peer_ht_rates.num_rates);

	ptr += sizeof(*tlv);
	ptr += ht_rate_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VHT_RATE_SET);
	tlv->len = __cpu_to_le16(sizeof(*vht_rate));
	vht_rate = (void *)tlv->value;

	vht_rate->rx_max_rate = __cpu_to_le32(arg->peer_vht_rates.rx_max_rate);
	vht_rate->rx_mcs_set = __cpu_to_le32(arg->peer_vht_rates.rx_mcs_set);
	vht_rate->tx_max_rate = __cpu_to_le32(arg->peer_vht_rates.tx_max_rate);
	vht_rate->tx_mcs_set = __cpu_to_le32(arg->peer_vht_rates.tx_mcs_set);

	ptr += sizeof(*tlv);
	ptr += sizeof(*vht_rate);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer assoc\n");
	return skb;
}