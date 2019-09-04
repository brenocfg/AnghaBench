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
struct xdp_sock {scalar_t__ tx; scalar_t__ rx; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 unsigned int datagram_poll (struct file*,struct socket*,struct poll_table_struct*) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int /*<<< orphan*/  xskq_empty_desc (scalar_t__) ; 
 int /*<<< orphan*/  xskq_full_desc (scalar_t__) ; 

__attribute__((used)) static unsigned int xsk_poll(struct file *file, struct socket *sock,
			     struct poll_table_struct *wait)
{
	unsigned int mask = datagram_poll(file, sock, wait);
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);

	if (xs->rx && !xskq_empty_desc(xs->rx))
		mask |= POLLIN | POLLRDNORM;
	if (xs->tx && !xskq_full_desc(xs->tx))
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}