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
struct sock {scalar_t__ sk_family; scalar_t__ sk_prot; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int TLSV4 ; 
 int TLSV6 ; 
 int /*<<< orphan*/  build_protos (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ saved_tcpv4_prot ; 
 scalar_t__ saved_tcpv6_prot ; 
 scalar_t__ smp_load_acquire (scalar_t__*) ; 
 int /*<<< orphan*/  smp_store_release (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  tcpv4_prot_mutex ; 
 int /*<<< orphan*/  tcpv6_prot_mutex ; 
 int /*<<< orphan*/ * tls_prots ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tls_build_proto(struct sock *sk)
{
	int ip_ver = sk->sk_family == AF_INET6 ? TLSV6 : TLSV4;

	/* Build IPv6 TLS whenever the address of tcpv6 _prot changes */
	if (ip_ver == TLSV6 &&
	    unlikely(sk->sk_prot != smp_load_acquire(&saved_tcpv6_prot))) {
		mutex_lock(&tcpv6_prot_mutex);
		if (likely(sk->sk_prot != saved_tcpv6_prot)) {
			build_protos(tls_prots[TLSV6], sk->sk_prot);
			smp_store_release(&saved_tcpv6_prot, sk->sk_prot);
		}
		mutex_unlock(&tcpv6_prot_mutex);
	}

	if (ip_ver == TLSV4 &&
	    unlikely(sk->sk_prot != smp_load_acquire(&saved_tcpv4_prot))) {
		mutex_lock(&tcpv4_prot_mutex);
		if (likely(sk->sk_prot != saved_tcpv4_prot)) {
			build_protos(tls_prots[TLSV4], sk->sk_prot);
			smp_store_release(&saved_tcpv4_prot, sk->sk_prot);
		}
		mutex_unlock(&tcpv4_prot_mutex);
	}
}