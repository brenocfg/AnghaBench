#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcp_fastopen_cookie {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct tcp_fastopen_context {int /*<<< orphan*/  tfm; } ;
struct sock {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {TYPE_1__ fastopenq; } ;
struct TYPE_10__ {TYPE_2__ icsk_accept_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  tcp_fastopen_ctx; } ;
struct TYPE_9__ {TYPE_3__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_FASTOPEN_COOKIE_SIZE ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 TYPE_5__* inet_csk (struct sock*) ; 
 struct tcp_fastopen_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_4__* sock_net (struct sock*) ; 

__attribute__((used)) static bool __tcp_fastopen_cookie_gen(struct sock *sk, const void *path,
				      struct tcp_fastopen_cookie *foc)
{
	struct tcp_fastopen_context *ctx;
	bool ok = false;

	rcu_read_lock();

	ctx = rcu_dereference(inet_csk(sk)->icsk_accept_queue.fastopenq.ctx);
	if (!ctx)
		ctx = rcu_dereference(sock_net(sk)->ipv4.tcp_fastopen_ctx);

	if (ctx) {
		crypto_cipher_encrypt_one(ctx->tfm, foc->val, path);
		foc->len = TCP_FASTOPEN_COOKIE_SIZE;
		ok = true;
	}
	rcu_read_unlock();
	return ok;
}