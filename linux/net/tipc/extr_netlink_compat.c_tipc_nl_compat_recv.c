#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tipc_nl_compat_msg {int cmd; TYPE_1__* rep; int /*<<< orphan*/  net; scalar_t__ req_size; scalar_t__ req; int /*<<< orphan*/  dst_sk; } ;
struct tipc_genlmsghdr {int cmd; } ;
struct sk_buff {int /*<<< orphan*/  sk; scalar_t__ data; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_len; } ;
struct genl_info {int /*<<< orphan*/  nlhdr; struct tipc_genlmsghdr* userhdr; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ GENL_HDRLEN ; 
 TYPE_4__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TIPC_CFG_NOT_NET_ADMIN ; 
 int /*<<< orphan*/  TIPC_CFG_NOT_SUPPORTED ; 
 int /*<<< orphan*/  TIPC_CFG_TLV_ERROR ; 
 scalar_t__ TIPC_GENL_HDRLEN ; 
 int /*<<< orphan*/  TLV_OK (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct nlmsghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tipc_nl_compat_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nlmsg_attrlen (struct nlmsghdr*,scalar_t__) ; 
 scalar_t__ nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (TYPE_1__*) ; 
 int nlmsg_total_size (scalar_t__) ; 
 int /*<<< orphan*/  skb_push (TYPE_1__*,int) ; 
 void* tipc_get_err_tlv (int /*<<< orphan*/ ) ; 
 int tipc_nl_compat_handle (struct tipc_nl_compat_msg*) ; 

__attribute__((used)) static int tipc_nl_compat_recv(struct sk_buff *skb, struct genl_info *info)
{
	int err;
	int len;
	struct tipc_nl_compat_msg msg;
	struct nlmsghdr *req_nlh;
	struct nlmsghdr *rep_nlh;
	struct tipc_genlmsghdr *req_userhdr = info->userhdr;

	memset(&msg, 0, sizeof(msg));

	req_nlh = (struct nlmsghdr *)skb->data;
	msg.req = nlmsg_data(req_nlh) + GENL_HDRLEN + TIPC_GENL_HDRLEN;
	msg.cmd = req_userhdr->cmd;
	msg.net = genl_info_net(info);
	msg.dst_sk = skb->sk;

	if ((msg.cmd & 0xC000) && (!netlink_net_capable(skb, CAP_NET_ADMIN))) {
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_NET_ADMIN);
		err = -EACCES;
		goto send;
	}

	msg.req_size = nlmsg_attrlen(req_nlh, GENL_HDRLEN + TIPC_GENL_HDRLEN);
	if (msg.req_size && !TLV_OK(msg.req, msg.req_size)) {
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_SUPPORTED);
		err = -EOPNOTSUPP;
		goto send;
	}

	err = tipc_nl_compat_handle(&msg);
	if ((err == -EOPNOTSUPP) || (err == -EPERM))
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_SUPPORTED);
	else if (err == -EINVAL)
		msg.rep = tipc_get_err_tlv(TIPC_CFG_TLV_ERROR);
send:
	if (!msg.rep)
		return err;

	len = nlmsg_total_size(GENL_HDRLEN + TIPC_GENL_HDRLEN);
	skb_push(msg.rep, len);
	rep_nlh = nlmsg_hdr(msg.rep);
	memcpy(rep_nlh, info->nlhdr, len);
	rep_nlh->nlmsg_len = msg.rep->len;
	genlmsg_unicast(msg.net, msg.rep, NETLINK_CB(skb).portid);

	return err;
}