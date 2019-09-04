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
struct sock {int /*<<< orphan*/  sk_v6_daddr; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  UDP6_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  UDP_MIB_RCVBUFERRORS ; 
 int __udp_enqueue_schedule_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_incoming_cpu_update (struct sock*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mark_napi_id_once (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int __udpv6_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	int rc;

	if (!ipv6_addr_any(&sk->sk_v6_daddr)) {
		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	} else {
		sk_mark_napi_id_once(sk, skb);
	}

	rc = __udp_enqueue_schedule_skb(sk, skb);
	if (rc < 0) {
		int is_udplite = IS_UDPLITE(sk);

		/* Note that an ENOMEM error is charged twice */
		if (rc == -ENOMEM)
			UDP6_INC_STATS(sock_net(sk),
					 UDP_MIB_RCVBUFERRORS, is_udplite);
		UDP6_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
		kfree_skb(skb);
		return -1;
	}

	return 0;
}