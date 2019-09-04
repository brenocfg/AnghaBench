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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_tlv_hdr {scalar_t__ val; void* len; void* type; } ;
struct qlink_cmd {int dummy; } ;
struct qlink_acl_data {int dummy; } ;
struct cfg80211_acl_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  QLINK_CMD_RESULT_INVALID 129 
#define  QLINK_CMD_RESULT_OK 128 
 int /*<<< orphan*/  QLINK_CMD_SET_MAC_ACL ; 
 size_t QTN_TLV_ID_ACL_DATA ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  qlink_acl_data_cfg2q (struct cfg80211_acl_data const*,struct qlink_acl_data*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 size_t qtnf_cmd_acl_data_size (struct cfg80211_acl_data const*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*,int*) ; 
 struct qlink_tlv_hdr* skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_set_mac_acl(const struct qtnf_vif *vif,
			 const struct cfg80211_acl_data *params)
{
	struct qtnf_bus *bus = vif->mac->bus;
	struct sk_buff *cmd_skb;
	struct qlink_tlv_hdr *tlv;
	size_t acl_size = qtnf_cmd_acl_data_size(params);
	u16 res_code;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_SET_MAC_ACL,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	tlv = skb_put(cmd_skb, sizeof(*tlv) + acl_size);
	tlv->type = cpu_to_le16(QTN_TLV_ID_ACL_DATA);
	tlv->len = cpu_to_le16(acl_size);
	qlink_acl_data_cfg2q(params, (struct qlink_acl_data *)tlv->val);

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb, &res_code);
	qtnf_bus_unlock(bus);

	if (unlikely(ret))
		return ret;

	switch (res_code) {
	case QLINK_CMD_RESULT_OK:
		break;
	case QLINK_CMD_RESULT_INVALID:
		ret = -EINVAL;
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}