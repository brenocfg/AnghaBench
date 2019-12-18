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
struct sock {int sk_state; TYPE_1__* sk_prot; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_flags; } ;
struct dccp_sock {size_t dccps_mss_cache; int /*<<< orphan*/  dccps_xmit_timer; } ;
struct TYPE_2__ {size_t max_header; } ;

/* Variables and functions */
 int DCCPF_OPEN ; 
 int DCCPF_PARTOPEN ; 
 int DCCP_CLOSED ; 
 int EAGAIN ; 
 int EMSGSIZE ; 
 int ENOTCONN ; 
 int const MSG_DONTWAIT ; 
 int dccp_msghdr_parse (struct msghdr*,struct sk_buff*) ; 
 scalar_t__ dccp_qpolicy_full (struct sock*) ; 
 int /*<<< orphan*/  dccp_qpolicy_push (struct sock*,struct sk_buff*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_write_xmit (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int sk_stream_wait_connect (struct sock*,long*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,size_t) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int,int const,int*) ; 
 long sock_sndtimeo (struct sock*,int const) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dccp_probe (struct sock*,size_t) ; 

int dccp_sendmsg(struct sock *sk, struct msghdr *msg, size_t len)
{
	const struct dccp_sock *dp = dccp_sk(sk);
	const int flags = msg->msg_flags;
	const int noblock = flags & MSG_DONTWAIT;
	struct sk_buff *skb;
	int rc, size;
	long timeo;

	trace_dccp_probe(sk, len);

	if (len > dp->dccps_mss_cache)
		return -EMSGSIZE;

	lock_sock(sk);

	if (dccp_qpolicy_full(sk)) {
		rc = -EAGAIN;
		goto out_release;
	}

	timeo = sock_sndtimeo(sk, noblock);

	/*
	 * We have to use sk_stream_wait_connect here to set sk_write_pending,
	 * so that the trick in dccp_rcv_request_sent_state_process.
	 */
	/* Wait for a connection to finish. */
	if ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PARTOPEN))
		if ((rc = sk_stream_wait_connect(sk, &timeo)) != 0)
			goto out_release;

	size = sk->sk_prot->max_header + len;
	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, noblock, &rc);
	lock_sock(sk);
	if (skb == NULL)
		goto out_release;

	if (sk->sk_state == DCCP_CLOSED) {
		rc = -ENOTCONN;
		goto out_discard;
	}

	skb_reserve(skb, sk->sk_prot->max_header);
	rc = memcpy_from_msg(skb_put(skb, len), msg, len);
	if (rc != 0)
		goto out_discard;

	rc = dccp_msghdr_parse(msg, skb);
	if (rc != 0)
		goto out_discard;

	dccp_qpolicy_push(sk, skb);
	/*
	 * The xmit_timer is set if the TX CCID is rate-based and will expire
	 * when congestion control permits to release further packets into the
	 * network. Window-based CCIDs do not use this timer.
	 */
	if (!timer_pending(&dp->dccps_xmit_timer))
		dccp_write_xmit(sk);
out_release:
	release_sock(sk);
	return rc ? : len;
out_discard:
	kfree_skb(skb);
	goto out_release;
}