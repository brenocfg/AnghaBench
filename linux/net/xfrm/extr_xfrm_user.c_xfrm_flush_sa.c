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
struct xfrm_usersa_flush {int /*<<< orphan*/  proto; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
struct km_event {struct net* net; int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; int /*<<< orphan*/  event; TYPE_1__ data; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  km_state_notify (int /*<<< orphan*/ *,struct km_event*) ; 
 struct xfrm_usersa_flush* nlmsg_data (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int xfrm_state_flush (struct net*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int xfrm_flush_sa(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct km_event c;
	struct xfrm_usersa_flush *p = nlmsg_data(nlh);
	int err;

	err = xfrm_state_flush(net, p->proto, true, false);
	if (err) {
		if (err == -ESRCH) /* empty table */
			return 0;
		return err;
	}
	c.data.proto = p->proto;
	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.net = net;
	km_state_notify(NULL, &c);

	return 0;
}