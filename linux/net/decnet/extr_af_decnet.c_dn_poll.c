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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct file {int dummy; } ;
struct dn_scp {int /*<<< orphan*/  other_receive_queue; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  EPOLLRDBAND ; 
 int /*<<< orphan*/  datagram_poll (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dn_poll(struct file *file, struct socket *sock, poll_table  *wait)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	__poll_t mask = datagram_poll(file, sock, wait);

	if (!skb_queue_empty_lockless(&scp->other_receive_queue))
		mask |= EPOLLRDBAND;

	return mask;
}