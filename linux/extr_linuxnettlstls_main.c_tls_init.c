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
struct tls_context {void* rx_conf; void* tx_conf; } ;
struct sock {scalar_t__ sk_family; scalar_t__ sk_state; scalar_t__ sk_prot; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int TLSV4 ; 
 int TLSV6 ; 
 void* TLS_BASE ; 
 int /*<<< orphan*/  build_protos (int /*<<< orphan*/ ,scalar_t__) ; 
 struct tls_context* create_ctx (struct sock*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ saved_tcpv6_prot ; 
 scalar_t__ smp_load_acquire (scalar_t__*) ; 
 int /*<<< orphan*/  smp_store_release (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  tcpv6_prot_mutex ; 
 scalar_t__ tls_hw_prot (struct sock*) ; 
 int /*<<< orphan*/ * tls_prots ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_sk_prot (struct sock*,struct tls_context*) ; 

__attribute__((used)) static int tls_init(struct sock *sk)
{
	int ip_ver = sk->sk_family == AF_INET6 ? TLSV6 : TLSV4;
	struct tls_context *ctx;
	int rc = 0;

	if (tls_hw_prot(sk))
		goto out;

	/* The TLS ulp is currently supported only for TCP sockets
	 * in ESTABLISHED state.
	 * Supporting sockets in LISTEN state will require us
	 * to modify the accept implementation to clone rather then
	 * share the ulp context.
	 */
	if (sk->sk_state != TCP_ESTABLISHED)
		return -ENOTSUPP;

	/* allocate tls context */
	ctx = create_ctx(sk);
	if (!ctx) {
		rc = -ENOMEM;
		goto out;
	}

	/* Build IPv6 TLS whenever the address of tcpv6	_prot changes */
	if (ip_ver == TLSV6 &&
	    unlikely(sk->sk_prot != smp_load_acquire(&saved_tcpv6_prot))) {
		mutex_lock(&tcpv6_prot_mutex);
		if (likely(sk->sk_prot != saved_tcpv6_prot)) {
			build_protos(tls_prots[TLSV6], sk->sk_prot);
			smp_store_release(&saved_tcpv6_prot, sk->sk_prot);
		}
		mutex_unlock(&tcpv6_prot_mutex);
	}

	ctx->tx_conf = TLS_BASE;
	ctx->rx_conf = TLS_BASE;
	update_sk_prot(sk, ctx);
out:
	return rc;
}