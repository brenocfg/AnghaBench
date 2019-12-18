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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_seq; int /*<<< orphan*/  sadb_msg_pid; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct km_event {struct net* net; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; int /*<<< orphan*/  event; TYPE_1__ data; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  XFRM_MSG_FLUSHPOLICY ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  km_policy_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct km_event*) ; 
 struct net* sock_net (struct sock*) ; 
 int unicast_flush_resp (struct sock*,struct sadb_msg const*) ; 
 int xfrm_policy_flush (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pfkey_spdflush(struct sock *sk, struct sk_buff *skb, const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	struct net *net = sock_net(sk);
	struct km_event c;
	int err, err2;

	err = xfrm_policy_flush(net, XFRM_POLICY_TYPE_MAIN, true);
	err2 = unicast_flush_resp(sk, hdr);
	if (err || err2) {
		if (err == -ESRCH) /* empty table - old silent behavior */
			return 0;
		return err;
	}

	c.data.type = XFRM_POLICY_TYPE_MAIN;
	c.event = XFRM_MSG_FLUSHPOLICY;
	c.portid = hdr->sadb_msg_pid;
	c.seq = hdr->sadb_msg_seq;
	c.net = net;
	km_policy_notify(NULL, 0, &c);

	return 0;
}