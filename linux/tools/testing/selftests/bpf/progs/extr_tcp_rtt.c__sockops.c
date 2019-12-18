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
struct tcp_rtt_storage {int /*<<< orphan*/  icsk_retransmits; int /*<<< orphan*/  delivered_ce; int /*<<< orphan*/  delivered; int /*<<< orphan*/  dsack_dups; int /*<<< orphan*/  invoked; } ;
struct bpf_tcp_sock {int /*<<< orphan*/  icsk_retransmits; int /*<<< orphan*/  delivered_ce; int /*<<< orphan*/  delivered; int /*<<< orphan*/  dsack_dups; } ;
struct bpf_sock_ops {struct bpf_sock* sk; scalar_t__ op; } ;
struct bpf_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
 int BPF_SOCK_OPS_RTT_CB ; 
 int /*<<< orphan*/  BPF_SOCK_OPS_RTT_CB_FLAG ; 
 int BPF_SOCK_OPS_TCP_CONNECT_CB ; 
 struct tcp_rtt_storage* bpf_sk_storage_get (int /*<<< orphan*/ *,struct bpf_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_sock_ops_cb_flags_set (struct bpf_sock_ops*,int /*<<< orphan*/ ) ; 
 struct bpf_tcp_sock* bpf_tcp_sock (struct bpf_sock*) ; 
 int /*<<< orphan*/  socket_storage_map ; 

int _sockops(struct bpf_sock_ops *ctx)
{
	struct tcp_rtt_storage *storage;
	struct bpf_tcp_sock *tcp_sk;
	int op = (int) ctx->op;
	struct bpf_sock *sk;

	sk = ctx->sk;
	if (!sk)
		return 1;

	storage = bpf_sk_storage_get(&socket_storage_map, sk, 0,
				     BPF_SK_STORAGE_GET_F_CREATE);
	if (!storage)
		return 1;

	if (op == BPF_SOCK_OPS_TCP_CONNECT_CB) {
		bpf_sock_ops_cb_flags_set(ctx, BPF_SOCK_OPS_RTT_CB_FLAG);
		return 1;
	}

	if (op != BPF_SOCK_OPS_RTT_CB)
		return 1;

	tcp_sk = bpf_tcp_sock(sk);
	if (!tcp_sk)
		return 1;

	storage->invoked++;

	storage->dsack_dups = tcp_sk->dsack_dups;
	storage->delivered = tcp_sk->delivered;
	storage->delivered_ce = tcp_sk->delivered_ce;
	storage->icsk_retransmits = tcp_sk->icsk_retransmits;

	return 1;
}