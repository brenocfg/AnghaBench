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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct regulatory_request {int initiator; int user_reg_hint_type; int /*<<< orphan*/ * alpha2; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_cmd_reg_notify {int /*<<< orphan*/  user_reg_hint_type; int /*<<< orphan*/  initiator; int /*<<< orphan*/ * alpha2; } ;

/* Variables and functions */
 int EALREADY ; 
 int EFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  NL80211_REGDOM_SET_BY_CORE 137 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 136 
#define  NL80211_REGDOM_SET_BY_DRIVER 135 
#define  NL80211_REGDOM_SET_BY_USER 134 
#define  NL80211_USER_REG_HINT_CELL_BASE 133 
#define  NL80211_USER_REG_HINT_INDOOR 132 
#define  NL80211_USER_REG_HINT_USER 131 
 int /*<<< orphan*/  QLINK_CMD_REG_NOTIFY ; 
#define  QLINK_CMD_RESULT_EALREADY 130 
#define  QLINK_CMD_RESULT_ENOTSUPP 129 
#define  QLINK_CMD_RESULT_OK 128 
 int /*<<< orphan*/  QLINK_MACID_RSVD ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_CORE ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_COUNTRY_IE ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_USER ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_CELL_BASE ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_INDOOR ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_USER ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*,int*) ; 

int qtnf_cmd_reg_notify(struct qtnf_bus *bus, struct regulatory_request *req)
{
	struct sk_buff *cmd_skb;
	int ret;
	u16 res_code;
	struct qlink_cmd_reg_notify *cmd;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_REG_NOTIFY,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_reg_notify *)cmd_skb->data;
	cmd->alpha2[0] = req->alpha2[0];
	cmd->alpha2[1] = req->alpha2[1];

	switch (req->initiator) {
	case NL80211_REGDOM_SET_BY_CORE:
		cmd->initiator = QLINK_REGDOM_SET_BY_CORE;
		break;
	case NL80211_REGDOM_SET_BY_USER:
		cmd->initiator = QLINK_REGDOM_SET_BY_USER;
		break;
	case NL80211_REGDOM_SET_BY_DRIVER:
		cmd->initiator = QLINK_REGDOM_SET_BY_DRIVER;
		break;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		cmd->initiator = QLINK_REGDOM_SET_BY_COUNTRY_IE;
		break;
	}

	switch (req->user_reg_hint_type) {
	case NL80211_USER_REG_HINT_USER:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_USER;
		break;
	case NL80211_USER_REG_HINT_CELL_BASE:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_CELL_BASE;
		break;
	case NL80211_USER_REG_HINT_INDOOR:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_INDOOR;
		break;
	}

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send(bus, cmd_skb, &res_code);
	if (ret)
		goto out;

	switch (res_code) {
	case QLINK_CMD_RESULT_ENOTSUPP:
		pr_warn("reg update not supported\n");
		ret = -EOPNOTSUPP;
		break;
	case QLINK_CMD_RESULT_EALREADY:
		pr_info("regulatory domain is already set to %c%c",
			req->alpha2[0], req->alpha2[1]);
		ret = -EALREADY;
		break;
	case QLINK_CMD_RESULT_OK:
		ret = 0;
		break;
	default:
		ret = -EFAULT;
		break;
	}

out:
	qtnf_bus_unlock(bus);

	return ret;
}