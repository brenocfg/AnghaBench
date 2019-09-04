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
struct tls_context {int /*<<< orphan*/  sk_proto_close; int /*<<< orphan*/  getsockopt; int /*<<< orphan*/  setsockopt; } ;
struct sock {TYPE_1__* sk_prot; } ;
struct inet_connection_sock {struct tls_context* icsk_ulp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  close; int /*<<< orphan*/  getsockopt; int /*<<< orphan*/  setsockopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct tls_context* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tls_context *create_ctx(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tls_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx)
		return NULL;

	icsk->icsk_ulp_data = ctx;
	ctx->setsockopt = sk->sk_prot->setsockopt;
	ctx->getsockopt = sk->sk_prot->getsockopt;
	ctx->sk_proto_close = sk->sk_prot->close;
	return ctx;
}