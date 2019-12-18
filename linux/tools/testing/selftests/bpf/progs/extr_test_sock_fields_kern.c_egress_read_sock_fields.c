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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct bpf_tcp_sock {int dummy; } ;
struct bpf_spinlock_cnt {int cnt; int /*<<< orphan*/  lock; } ;
struct bpf_sock {int state; scalar_t__ family; scalar_t__ protocol; scalar_t__ src_port; int /*<<< orphan*/  src_ip6; } ;
struct __sk_buff {struct bpf_sock* sk; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ ADDR_CLI_IDX ; 
 scalar_t__ ADDR_SRV_IDX ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
 scalar_t__ EGRESS_CLI_IDX ; 
 scalar_t__ EGRESS_LINUM_IDX ; 
 scalar_t__ EGRESS_SRV_IDX ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  RETURN ; 
 int /*<<< orphan*/  addr_map ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ bpf_ntohs (int /*<<< orphan*/ ) ; 
 struct bpf_sock* bpf_sk_fullsock (struct bpf_sock*) ; 
 struct bpf_spinlock_cnt* bpf_sk_storage_get (int /*<<< orphan*/ *,struct bpf_sock*,struct bpf_spinlock_cnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_spin_unlock (int /*<<< orphan*/ *) ; 
 struct bpf_tcp_sock* bpf_tcp_sock (struct bpf_sock*) ; 
 int /*<<< orphan*/  is_loopback6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_pkt_out_cnt ; 
 int /*<<< orphan*/  sk_pkt_out_cnt10 ; 
 int /*<<< orphan*/  skcpy (struct bpf_sock*,struct bpf_sock*) ; 
 int /*<<< orphan*/  sock_result_map ; 
 int /*<<< orphan*/  tcp_sock_result_map ; 
 int /*<<< orphan*/  tpcpy (struct bpf_tcp_sock*,struct bpf_tcp_sock*) ; 

int egress_read_sock_fields(struct __sk_buff *skb)
{
	struct bpf_spinlock_cnt cli_cnt_init = { .lock = 0, .cnt = 0xeB9F };
	__u32 srv_idx = ADDR_SRV_IDX, cli_idx = ADDR_CLI_IDX, result_idx;
	struct bpf_spinlock_cnt *pkt_out_cnt, *pkt_out_cnt10;
	struct sockaddr_in6 *srv_sa6, *cli_sa6;
	struct bpf_tcp_sock *tp, *tp_ret;
	struct bpf_sock *sk, *sk_ret;
	__u32 linum, linum_idx;

	linum_idx = EGRESS_LINUM_IDX;

	sk = skb->sk;
	if (!sk || sk->state == 10)
		RETURN;

	sk = bpf_sk_fullsock(sk);
	if (!sk || sk->family != AF_INET6 || sk->protocol != IPPROTO_TCP ||
	    !is_loopback6(sk->src_ip6))
		RETURN;

	tp = bpf_tcp_sock(sk);
	if (!tp)
		RETURN;

	srv_sa6 = bpf_map_lookup_elem(&addr_map, &srv_idx);
	cli_sa6 = bpf_map_lookup_elem(&addr_map, &cli_idx);
	if (!srv_sa6 || !cli_sa6)
		RETURN;

	if (sk->src_port == bpf_ntohs(srv_sa6->sin6_port))
		result_idx = EGRESS_SRV_IDX;
	else if (sk->src_port == bpf_ntohs(cli_sa6->sin6_port))
		result_idx = EGRESS_CLI_IDX;
	else
		RETURN;

	sk_ret = bpf_map_lookup_elem(&sock_result_map, &result_idx);
	tp_ret = bpf_map_lookup_elem(&tcp_sock_result_map, &result_idx);
	if (!sk_ret || !tp_ret)
		RETURN;

	skcpy(sk_ret, sk);
	tpcpy(tp_ret, tp);

	if (result_idx == EGRESS_SRV_IDX) {
		/* The userspace has created it for srv sk */
		pkt_out_cnt = bpf_sk_storage_get(&sk_pkt_out_cnt, sk, 0, 0);
		pkt_out_cnt10 = bpf_sk_storage_get(&sk_pkt_out_cnt10, sk,
						   0, 0);
	} else {
		pkt_out_cnt = bpf_sk_storage_get(&sk_pkt_out_cnt, sk,
						 &cli_cnt_init,
						 BPF_SK_STORAGE_GET_F_CREATE);
		pkt_out_cnt10 = bpf_sk_storage_get(&sk_pkt_out_cnt10,
						   sk, &cli_cnt_init,
						   BPF_SK_STORAGE_GET_F_CREATE);
	}

	if (!pkt_out_cnt || !pkt_out_cnt10)
		RETURN;

	/* Even both cnt and cnt10 have lock defined in their BTF,
	 * intentionally one cnt takes lock while one does not
	 * as a test for the spinlock support in BPF_MAP_TYPE_SK_STORAGE.
	 */
	pkt_out_cnt->cnt += 1;
	bpf_spin_lock(&pkt_out_cnt10->lock);
	pkt_out_cnt10->cnt += 10;
	bpf_spin_unlock(&pkt_out_cnt10->lock);

	RETURN;
}