#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct l2tp_tunnel {int dummy; } ;
struct l2tp_session {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2TP_CMD_SESSION_GET ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 scalar_t__ l2tp_nl_session_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2tp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 struct l2tp_session* l2tp_session_get_nth (struct l2tp_tunnel*,int) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 struct l2tp_tunnel* l2tp_tunnel_get_nth (struct net*,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_nl_cmd_session_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct l2tp_session *session;
	struct l2tp_tunnel *tunnel = NULL;
	int ti = cb->args[0];
	int si = cb->args[1];

	for (;;) {
		if (tunnel == NULL) {
			tunnel = l2tp_tunnel_get_nth(net, ti);
			if (tunnel == NULL)
				goto out;
		}

		session = l2tp_session_get_nth(tunnel, si);
		if (session == NULL) {
			ti++;
			l2tp_tunnel_dec_refcount(tunnel);
			tunnel = NULL;
			si = 0;
			continue;
		}

		if (l2tp_nl_session_send(skb, NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 session, L2TP_CMD_SESSION_GET) < 0) {
			l2tp_session_dec_refcount(session);
			l2tp_tunnel_dec_refcount(tunnel);
			break;
		}
		l2tp_session_dec_refcount(session);

		si++;
	}

out:
	cb->args[0] = ti;
	cb->args[1] = si;

	return skb->len;
}