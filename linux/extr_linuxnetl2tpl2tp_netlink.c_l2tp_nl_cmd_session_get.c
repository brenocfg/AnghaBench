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
struct sk_buff {int dummy; } ;
struct l2tp_session {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  L2TP_CMD_SESSION_GET ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct l2tp_session* l2tp_nl_session_get (struct genl_info*) ; 
 int l2tp_nl_session_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2tp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_nl_cmd_session_get(struct sk_buff *skb, struct genl_info *info)
{
	struct l2tp_session *session;
	struct sk_buff *msg;
	int ret;

	session = l2tp_nl_session_get(info);
	if (session == NULL) {
		ret = -ENODEV;
		goto err;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto err_ref;
	}

	ret = l2tp_nl_session_send(msg, info->snd_portid, info->snd_seq,
				   0, session, L2TP_CMD_SESSION_GET);
	if (ret < 0)
		goto err_ref_msg;

	ret = genlmsg_unicast(genl_info_net(info), msg, info->snd_portid);

	l2tp_session_dec_refcount(session);

	return ret;

err_ref_msg:
	nlmsg_free(msg);
err_ref:
	l2tp_session_dec_refcount(session);
err:
	return ret;
}