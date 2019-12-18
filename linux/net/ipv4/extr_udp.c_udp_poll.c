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
struct socket {struct sock* sk; } ;
struct sock {int sk_shutdown; } ;
struct file {int f_flags; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  reader_queue; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int O_NONBLOCK ; 
 int RCV_SHUTDOWN ; 
 int datagram_poll (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 int first_packet_length (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

__poll_t udp_poll(struct file *file, struct socket *sock, poll_table *wait)
{
	__poll_t mask = datagram_poll(file, sock, wait);
	struct sock *sk = sock->sk;

	if (!skb_queue_empty_lockless(&udp_sk(sk)->reader_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Check for false positives due to checksum errors */
	if ((mask & EPOLLRDNORM) && !(file->f_flags & O_NONBLOCK) &&
	    !(sk->sk_shutdown & RCV_SHUTDOWN) && first_packet_length(sk) == -1)
		mask &= ~(EPOLLIN | EPOLLRDNORM);

	return mask;

}