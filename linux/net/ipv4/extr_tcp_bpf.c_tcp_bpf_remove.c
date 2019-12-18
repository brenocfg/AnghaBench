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
struct sock {int dummy; } ;
struct sk_psock_link {int dummy; } ;
struct sk_psock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_psock_free_link (struct sk_psock_link*) ; 
 struct sk_psock_link* sk_psock_link_pop (struct sk_psock*) ; 
 int /*<<< orphan*/  sk_psock_unlink (struct sock*,struct sk_psock_link*) ; 

__attribute__((used)) static void tcp_bpf_remove(struct sock *sk, struct sk_psock *psock)
{
	struct sk_psock_link *link;

	while ((link = sk_psock_link_pop(psock))) {
		sk_psock_unlink(sk, link);
		sk_psock_free_link(link);
	}
}