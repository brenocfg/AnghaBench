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
struct TYPE_4__ {void* s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {scalar_t__ daddr; void* dport; struct sockaddr_in sport; struct sockaddr_in saddr; } ;
struct bpf_sock_tuple {TYPE_1__ ipv4; } ;
struct bpf_sock_addr {scalar_t__ type; void* user_port; void* user_ip4; } ;
struct bpf_sock {scalar_t__ src_ip4; scalar_t__ src_port; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BPF_F_CURRENT_NETNS ; 
 int /*<<< orphan*/  DST_REWRITE_IP4 ; 
 scalar_t__ DST_REWRITE_PORT4 ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SRC_REWRITE_IP4 ; 
 scalar_t__ bpf_bind (struct bpf_sock_addr*,struct sockaddr*,int) ; 
 void* bpf_htonl (int /*<<< orphan*/ ) ; 
 void* bpf_htons (scalar_t__) ; 
 struct bpf_sock* bpf_sk_lookup_tcp (struct bpf_sock_addr*,struct bpf_sock_tuple*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_sock* bpf_sk_lookup_udp (struct bpf_sock_addr*,struct bpf_sock_tuple*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_sk_release (struct bpf_sock*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

int connect_v4_prog(struct bpf_sock_addr *ctx)
{
	struct bpf_sock_tuple tuple = {};
	struct sockaddr_in sa;
	struct bpf_sock *sk;

	/* Verify that new destination is available. */
	memset(&tuple.ipv4.saddr, 0, sizeof(tuple.ipv4.saddr));
	memset(&tuple.ipv4.sport, 0, sizeof(tuple.ipv4.sport));

	tuple.ipv4.daddr = bpf_htonl(DST_REWRITE_IP4);
	tuple.ipv4.dport = bpf_htons(DST_REWRITE_PORT4);

	if (ctx->type != SOCK_STREAM && ctx->type != SOCK_DGRAM)
		return 0;
	else if (ctx->type == SOCK_STREAM)
		sk = bpf_sk_lookup_tcp(ctx, &tuple, sizeof(tuple.ipv4),
				       BPF_F_CURRENT_NETNS, 0);
	else
		sk = bpf_sk_lookup_udp(ctx, &tuple, sizeof(tuple.ipv4),
				       BPF_F_CURRENT_NETNS, 0);

	if (!sk)
		return 0;

	if (sk->src_ip4 != tuple.ipv4.daddr ||
	    sk->src_port != DST_REWRITE_PORT4) {
		bpf_sk_release(sk);
		return 0;
	}

	bpf_sk_release(sk);

	/* Rewrite destination. */
	ctx->user_ip4 = bpf_htonl(DST_REWRITE_IP4);
	ctx->user_port = bpf_htons(DST_REWRITE_PORT4);

	/* Rewrite source. */
	memset(&sa, 0, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = bpf_htons(0);
	sa.sin_addr.s_addr = bpf_htonl(SRC_REWRITE_IP4);

	if (bpf_bind(ctx, (struct sockaddr *)&sa, sizeof(sa)) != 0)
		return 0;

	return 1;
}