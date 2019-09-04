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
struct xdp_sock {int /*<<< orphan*/  umem; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  sk_refcnt_debug_dec (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_del_sk_umem (int /*<<< orphan*/ ,struct xdp_sock*) ; 
 int /*<<< orphan*/  xdp_put_umem (int /*<<< orphan*/ ) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int /*<<< orphan*/  xskq_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xsk_destruct(struct sock *sk)
{
	struct xdp_sock *xs = xdp_sk(sk);

	if (!sock_flag(sk, SOCK_DEAD))
		return;

	xskq_destroy(xs->rx);
	xskq_destroy(xs->tx);
	xdp_del_sk_umem(xs->umem, xs);
	xdp_put_umem(xs->umem);

	sk_refcnt_debug_dec(sk);
}