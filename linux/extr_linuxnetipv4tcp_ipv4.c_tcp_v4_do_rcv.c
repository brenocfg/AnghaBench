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
struct sock {scalar_t__ sk_state; struct dst_entry* sk_rx_dst; } ;
struct sk_buff {scalar_t__ skb_iif; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ rx_dst_ifindex; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_checksum_complete (struct sk_buff*) ; 
 scalar_t__ tcp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_rcv_established (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_rcv_state_process (struct sock*,struct sk_buff*) ; 
 struct sock* tcp_v4_cookie_check (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_send_reset (struct sock*,struct sk_buff*) ; 

int tcp_v4_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct sock *rsk;

	if (sk->sk_state == TCP_ESTABLISHED) { /* Fast path */
		struct dst_entry *dst = sk->sk_rx_dst;

		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		if (dst) {
			if (inet_sk(sk)->rx_dst_ifindex != skb->skb_iif ||
			    !dst->ops->check(dst, 0)) {
				dst_release(dst);
				sk->sk_rx_dst = NULL;
			}
		}
		tcp_rcv_established(sk, skb);
		return 0;
	}

	if (tcp_checksum_complete(skb))
		goto csum_err;

	if (sk->sk_state == TCP_LISTEN) {
		struct sock *nsk = tcp_v4_cookie_check(sk, skb);

		if (!nsk)
			goto discard;
		if (nsk != sk) {
			if (tcp_child_process(sk, nsk, skb)) {
				rsk = nsk;
				goto reset;
			}
			return 0;
		}
	} else
		sock_rps_save_rxhash(sk, skb);

	if (tcp_rcv_state_process(sk, skb)) {
		rsk = sk;
		goto reset;
	}
	return 0;

reset:
	tcp_v4_send_reset(rsk, skb);
discard:
	kfree_skb(skb);
	/* Be careful here. If this function gets more complicated and
	 * gcc suffers from register pressure on the x86, sk (in %ebx)
	 * might be destroyed here. This current version compiles correctly,
	 * but you have been warned.
	 */
	return 0;

csum_err:
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
	goto discard;
}