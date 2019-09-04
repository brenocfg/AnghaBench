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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct ip_options {int /*<<< orphan*/  __data; int /*<<< orphan*/  optlen; } ;
struct TYPE_3__ {scalar_t__ optlen; } ;
struct TYPE_4__ {TYPE_1__ opt; } ;

/* Variables and functions */
 TYPE_2__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP_RETOPTS ; 
 int /*<<< orphan*/  MSG_CTRUNC ; 
 int /*<<< orphan*/  SOL_IP ; 
 scalar_t__ ip_options_echo (struct net*,struct ip_options*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_undo (struct ip_options*) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip_cmsg_recv_retopts(struct net *net, struct msghdr *msg,
				 struct sk_buff *skb)
{
	unsigned char optbuf[sizeof(struct ip_options) + 40];
	struct ip_options *opt = (struct ip_options *)optbuf;

	if (IPCB(skb)->opt.optlen == 0)
		return;

	if (ip_options_echo(net, opt, skb)) {
		msg->msg_flags |= MSG_CTRUNC;
		return;
	}
	ip_options_undo(opt);

	put_cmsg(msg, SOL_IP, IP_RETOPTS, opt->optlen, opt->__data);
}