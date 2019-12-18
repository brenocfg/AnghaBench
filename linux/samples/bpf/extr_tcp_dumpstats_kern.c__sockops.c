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
struct bpf_tcp_sock {int /*<<< orphan*/  icsk_retransmits; int /*<<< orphan*/  delivered_ce; int /*<<< orphan*/  delivered; int /*<<< orphan*/  dsack_dups; } ;
struct bpf_sock_ops {int op; struct bpf_sock* sk; } ;
struct bpf_sock {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
#define  BPF_SOCK_OPS_RTT_CB 129 
 int /*<<< orphan*/  BPF_SOCK_OPS_RTT_CB_FLAG ; 
#define  BPF_SOCK_OPS_TCP_CONNECT_CB 128 
 scalar_t__ INTERVAL ; 
 scalar_t__ bpf_ktime_get_ns () ; 
 int /*<<< orphan*/  bpf_next_dump ; 
 int /*<<< orphan*/  bpf_printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* bpf_sk_storage_get (int /*<<< orphan*/ *,struct bpf_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_sock_ops_cb_flags_set (struct bpf_sock_ops*,int /*<<< orphan*/ ) ; 
 struct bpf_tcp_sock* bpf_tcp_sock (struct bpf_sock*) ; 

int _sockops(struct bpf_sock_ops *ctx)
{
	struct bpf_tcp_sock *tcp_sk;
	struct bpf_sock *sk;
	__u64 *next_dump;
	__u64 now;

	switch (ctx->op) {
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		bpf_sock_ops_cb_flags_set(ctx, BPF_SOCK_OPS_RTT_CB_FLAG);
		return 1;
	case BPF_SOCK_OPS_RTT_CB:
		break;
	default:
		return 1;
	}

	sk = ctx->sk;
	if (!sk)
		return 1;

	next_dump = bpf_sk_storage_get(&bpf_next_dump, sk, 0,
				       BPF_SK_STORAGE_GET_F_CREATE);
	if (!next_dump)
		return 1;

	now = bpf_ktime_get_ns();
	if (now < *next_dump)
		return 1;

	tcp_sk = bpf_tcp_sock(sk);
	if (!tcp_sk)
		return 1;

	*next_dump = now + INTERVAL;

	bpf_printk("dsack_dups=%u delivered=%u\n",
		   tcp_sk->dsack_dups, tcp_sk->delivered);
	bpf_printk("delivered_ce=%u icsk_retransmits=%u\n",
		   tcp_sk->delivered_ce, tcp_sk->icsk_retransmits);

	return 1;
}