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
struct sock {scalar_t__ sk_family; int /*<<< orphan*/ * sk_prot; } ;
struct smap_psock {scalar_t__ bpf_tx_msg; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int SOCKMAP_BASE ; 
 int SOCKMAP_IPV4 ; 
 int SOCKMAP_IPV6 ; 
 int SOCKMAP_TX ; 
 int /*<<< orphan*/ ** bpf_tcp_prots ; 

__attribute__((used)) static void update_sk_prot(struct sock *sk, struct smap_psock *psock)
{
	int family = sk->sk_family == AF_INET6 ? SOCKMAP_IPV6 : SOCKMAP_IPV4;
	int conf = psock->bpf_tx_msg ? SOCKMAP_TX : SOCKMAP_BASE;

	sk->sk_prot = &bpf_tcp_prots[family][conf];
}