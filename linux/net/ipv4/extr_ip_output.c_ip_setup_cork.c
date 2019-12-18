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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct rtable {TYPE_4__ dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  tsflags; int /*<<< orphan*/  transmit_time; int /*<<< orphan*/  mark; } ;
struct ipcm_cookie {TYPE_2__ sockc; int /*<<< orphan*/  priority; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  gso_size; int /*<<< orphan*/  addr; struct ip_options_rcu* opt; } ;
struct TYPE_7__ {scalar_t__ optlen; } ;
struct ip_options_rcu {TYPE_3__ opt; } ;
struct ip_options {int dummy; } ;
struct inet_cork {scalar_t__ tx_flags; int /*<<< orphan*/  transmit_time; int /*<<< orphan*/  priority; int /*<<< orphan*/  mark; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; scalar_t__ length; TYPE_4__* dst; int /*<<< orphan*/  gso_size; int /*<<< orphan*/  fragsize; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; scalar_t__ opt; } ;
struct TYPE_5__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IPCORK_OPT ; 
 int /*<<< orphan*/  dst_mtu (TYPE_4__*) ; 
 scalar_t__ ip_sk_use_pmtu (struct sock*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  sock_tx_timestamp (struct sock*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_setup_cork(struct sock *sk, struct inet_cork *cork,
			 struct ipcm_cookie *ipc, struct rtable **rtp)
{
	struct ip_options_rcu *opt;
	struct rtable *rt;

	rt = *rtp;
	if (unlikely(!rt))
		return -EFAULT;

	/*
	 * setup for corking.
	 */
	opt = ipc->opt;
	if (opt) {
		if (!cork->opt) {
			cork->opt = kmalloc(sizeof(struct ip_options) + 40,
					    sk->sk_allocation);
			if (unlikely(!cork->opt))
				return -ENOBUFS;
		}
		memcpy(cork->opt, &opt->opt, sizeof(struct ip_options) + opt->opt.optlen);
		cork->flags |= IPCORK_OPT;
		cork->addr = ipc->addr;
	}

	/*
	 * We steal reference to this route, caller should not release it
	 */
	*rtp = NULL;
	cork->fragsize = ip_sk_use_pmtu(sk) ?
			 dst_mtu(&rt->dst) : rt->dst.dev->mtu;

	cork->gso_size = ipc->gso_size;
	cork->dst = &rt->dst;
	cork->length = 0;
	cork->ttl = ipc->ttl;
	cork->tos = ipc->tos;
	cork->mark = ipc->sockc.mark;
	cork->priority = ipc->priority;
	cork->transmit_time = ipc->sockc.transmit_time;
	cork->tx_flags = 0;
	sock_tx_timestamp(sk, ipc->sockc.tsflags, &cork->tx_flags);

	return 0;
}