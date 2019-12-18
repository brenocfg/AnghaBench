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
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; int /*<<< orphan*/  sadb_msg_satype; } ;
struct net {int dummy; } ;
struct TYPE_2__ {unsigned int proto; } ;
struct km_event {struct net* net; int /*<<< orphan*/  event; int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; TYPE_1__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  XFRM_MSG_FLUSHSA ; 
 int /*<<< orphan*/  km_state_notify (int /*<<< orphan*/ *,struct km_event*) ; 
 unsigned int pfkey_satype2proto (int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int unicast_flush_resp (struct sock*,struct sadb_msg const*) ; 
 int xfrm_state_flush (struct net*,unsigned int,int,int) ; 

__attribute__((used)) static int pfkey_flush(struct sock *sk, struct sk_buff *skb, const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	struct net *net = sock_net(sk);
	unsigned int proto;
	struct km_event c;
	int err, err2;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	if (proto == 0)
		return -EINVAL;

	err = xfrm_state_flush(net, proto, true, false);
	err2 = unicast_flush_resp(sk, hdr);
	if (err || err2) {
		if (err == -ESRCH) /* empty table - go quietly */
			err = 0;
		return err ? err : err2;
	}

	c.data.proto = proto;
	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	c.event = XFRM_MSG_FLUSHSA;
	c.net = net;
	km_state_notify(NULL, &c);

	return 0;
}