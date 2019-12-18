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
struct inet_diag_msg {int /*<<< orphan*/  idiag_wqueue; int /*<<< orphan*/  idiag_rqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_wmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  udp_rqueue_get (struct sock*) ; 

__attribute__((used)) static void udp_diag_get_info(struct sock *sk, struct inet_diag_msg *r,
		void *info)
{
	r->idiag_rqueue = udp_rqueue_get(sk);
	r->idiag_wqueue = sk_wmem_alloc_get(sk);
}