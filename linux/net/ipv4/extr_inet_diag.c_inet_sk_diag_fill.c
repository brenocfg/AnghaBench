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
union tcp_cc_info {int /*<<< orphan*/  idiag_tmem; int /*<<< orphan*/  idiag_fmem; struct tcp_congestion_ops* idiag_wmem; int /*<<< orphan*/  idiag_rmem; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct user_namespace {int dummy; } ;
struct tcp_congestion_ops {size_t (* get_info ) (struct sock*,int,int*,union tcp_cc_info*) ;int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; scalar_t__ sk_priority; int /*<<< orphan*/  sk_cgrp_data; TYPE_1__ sk_timer; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_forward_alloc; int /*<<< orphan*/  sk_wmem_queued; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct inet_diag_req_v2 {int idiag_ext; size_t sdiag_protocol; } ;
struct inet_diag_msg {scalar_t__ idiag_state; int idiag_timer; void* idiag_expires; scalar_t__ idiag_retrans; } ;
struct inet_diag_meminfo {int /*<<< orphan*/  idiag_tmem; int /*<<< orphan*/  idiag_fmem; struct tcp_congestion_ops* idiag_wmem; int /*<<< orphan*/  idiag_rmem; } ;
struct inet_diag_handler {scalar_t__ (* idiag_get_aux ) (struct sock*,int,struct sk_buff*) ;int /*<<< orphan*/  (* idiag_get_info ) (struct sock*,struct inet_diag_msg*,void*) ;scalar_t__ idiag_info_size; } ;
struct inet_connection_sock {scalar_t__ icsk_pending; int /*<<< orphan*/  icsk_ca_ops; scalar_t__ icsk_probes_out; scalar_t__ icsk_timeout; scalar_t__ icsk_retransmits; } ;
typedef  int /*<<< orphan*/  minfo ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EMSGSIZE ; 
 scalar_t__ ICSK_TIME_LOSS_PROBE ; 
 scalar_t__ ICSK_TIME_PROBE0 ; 
 scalar_t__ ICSK_TIME_REO_TIMEOUT ; 
 scalar_t__ ICSK_TIME_RETRANS ; 
 int INET_DIAG_CLASS_ID ; 
 int INET_DIAG_CONG ; 
 int INET_DIAG_INFO ; 
 int INET_DIAG_MEMINFO ; 
 int /*<<< orphan*/  INET_DIAG_PAD ; 
 int /*<<< orphan*/  INET_DIAG_PROTOCOL ; 
 int INET_DIAG_SKMEMINFO ; 
 int INET_DIAG_TCLASS ; 
 struct tcp_congestion_ops* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ TCP_TIME_WAIT ; 
 scalar_t__ inet_diag_msg_attrs_fill (struct sock*,struct sk_buff*,struct inet_diag_msg*,int,struct user_namespace*,int) ; 
 int /*<<< orphan*/  inet_diag_msg_common_fill (struct inet_diag_msg*,struct sock*) ; 
 struct inet_diag_handler** inet_diag_table ; 
 scalar_t__ jiffies ; 
 void* jiffies_to_msecs (scalar_t__) ; 
 void* nla_data (struct nlattr*) ; 
 scalar_t__ nla_put (struct sk_buff*,int,size_t,union tcp_cc_info*) ; 
 int nla_put_string (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve_64bit (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct inet_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  sk_rmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  sk_wmem_alloc_get (struct sock*) ; 
 scalar_t__ sock_cgroup_classid (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_diag_put_meminfo (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct inet_diag_msg*,void*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,struct inet_diag_msg*,void*) ; 
 scalar_t__ stub3 (struct sock*,int,struct sk_buff*) ; 
 size_t stub4 (struct sock*,int,int*,union tcp_cc_info*) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

int inet_sk_diag_fill(struct sock *sk, struct inet_connection_sock *icsk,
		      struct sk_buff *skb, const struct inet_diag_req_v2 *req,
		      struct user_namespace *user_ns,
		      u32 portid, u32 seq, u16 nlmsg_flags,
		      const struct nlmsghdr *unlh,
		      bool net_admin)
{
	const struct tcp_congestion_ops *ca_ops;
	const struct inet_diag_handler *handler;
	int ext = req->idiag_ext;
	struct inet_diag_msg *r;
	struct nlmsghdr  *nlh;
	struct nlattr *attr;
	void *info = NULL;

	handler = inet_diag_table[req->sdiag_protocol];
	BUG_ON(!handler);

	nlh = nlmsg_put(skb, portid, seq, unlh->nlmsg_type, sizeof(*r),
			nlmsg_flags);
	if (!nlh)
		return -EMSGSIZE;

	r = nlmsg_data(nlh);
	BUG_ON(!sk_fullsock(sk));

	inet_diag_msg_common_fill(r, sk);
	r->idiag_state = sk->sk_state;
	r->idiag_timer = 0;
	r->idiag_retrans = 0;

	if (inet_diag_msg_attrs_fill(sk, skb, r, ext, user_ns, net_admin))
		goto errout;

	if (ext & (1 << (INET_DIAG_MEMINFO - 1))) {
		struct inet_diag_meminfo minfo = {
			.idiag_rmem = sk_rmem_alloc_get(sk),
			.idiag_wmem = READ_ONCE(sk->sk_wmem_queued),
			.idiag_fmem = sk->sk_forward_alloc,
			.idiag_tmem = sk_wmem_alloc_get(sk),
		};

		if (nla_put(skb, INET_DIAG_MEMINFO, sizeof(minfo), &minfo) < 0)
			goto errout;
	}

	if (ext & (1 << (INET_DIAG_SKMEMINFO - 1)))
		if (sock_diag_put_meminfo(sk, skb, INET_DIAG_SKMEMINFO))
			goto errout;

	/*
	 * RAW sockets might have user-defined protocols assigned,
	 * so report the one supplied on socket creation.
	 */
	if (sk->sk_type == SOCK_RAW) {
		if (nla_put_u8(skb, INET_DIAG_PROTOCOL, sk->sk_protocol))
			goto errout;
	}

	if (!icsk) {
		handler->idiag_get_info(sk, r, NULL);
		goto out;
	}

	if (icsk->icsk_pending == ICSK_TIME_RETRANS ||
	    icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) {
		r->idiag_timer = 1;
		r->idiag_retrans = icsk->icsk_retransmits;
		r->idiag_expires =
			jiffies_to_msecs(icsk->icsk_timeout - jiffies);
	} else if (icsk->icsk_pending == ICSK_TIME_PROBE0) {
		r->idiag_timer = 4;
		r->idiag_retrans = icsk->icsk_probes_out;
		r->idiag_expires =
			jiffies_to_msecs(icsk->icsk_timeout - jiffies);
	} else if (timer_pending(&sk->sk_timer)) {
		r->idiag_timer = 2;
		r->idiag_retrans = icsk->icsk_probes_out;
		r->idiag_expires =
			jiffies_to_msecs(sk->sk_timer.expires - jiffies);
	} else {
		r->idiag_timer = 0;
		r->idiag_expires = 0;
	}

	if ((ext & (1 << (INET_DIAG_INFO - 1))) && handler->idiag_info_size) {
		attr = nla_reserve_64bit(skb, INET_DIAG_INFO,
					 handler->idiag_info_size,
					 INET_DIAG_PAD);
		if (!attr)
			goto errout;

		info = nla_data(attr);
	}

	if (ext & (1 << (INET_DIAG_CONG - 1))) {
		int err = 0;

		rcu_read_lock();
		ca_ops = READ_ONCE(icsk->icsk_ca_ops);
		if (ca_ops)
			err = nla_put_string(skb, INET_DIAG_CONG, ca_ops->name);
		rcu_read_unlock();
		if (err < 0)
			goto errout;
	}

	handler->idiag_get_info(sk, r, info);

	if (ext & (1 << (INET_DIAG_INFO - 1)) && handler->idiag_get_aux)
		if (handler->idiag_get_aux(sk, net_admin, skb) < 0)
			goto errout;

	if (sk->sk_state < TCP_TIME_WAIT) {
		union tcp_cc_info info;
		size_t sz = 0;
		int attr;

		rcu_read_lock();
		ca_ops = READ_ONCE(icsk->icsk_ca_ops);
		if (ca_ops && ca_ops->get_info)
			sz = ca_ops->get_info(sk, ext, &attr, &info);
		rcu_read_unlock();
		if (sz && nla_put(skb, attr, sz, &info) < 0)
			goto errout;
	}

	if (ext & (1 << (INET_DIAG_CLASS_ID - 1)) ||
	    ext & (1 << (INET_DIAG_TCLASS - 1))) {
		u32 classid = 0;

#ifdef CONFIG_SOCK_CGROUP_DATA
		classid = sock_cgroup_classid(&sk->sk_cgrp_data);
#endif
		/* Fallback to socket priority if class id isn't set.
		 * Classful qdiscs use it as direct reference to class.
		 * For cgroup2 classid is always zero.
		 */
		if (!classid)
			classid = sk->sk_priority;

		if (nla_put_u32(skb, INET_DIAG_CLASS_ID, classid))
			goto errout;
	}

out:
	nlmsg_end(skb, nlh);
	return 0;

errout:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}