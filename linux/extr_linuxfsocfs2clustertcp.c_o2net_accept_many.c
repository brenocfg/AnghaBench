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
struct work_struct {int dummy; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int o2net_accept_one (struct socket*,int*) ; 
 struct socket* o2net_listen_sock ; 

__attribute__((used)) static void o2net_accept_many(struct work_struct *work)
{
	struct socket *sock = o2net_listen_sock;
	int	more;
	int	err;

	/*
	 * It is critical to note that due to interrupt moderation
	 * at the network driver level, we can't assume to get a
	 * softIRQ for every single conn since tcp SYN packets
	 * can arrive back-to-back, and therefore many pending
	 * accepts may result in just 1 softIRQ. If we terminate
	 * the o2net_accept_one() loop upon seeing an err, what happens
	 * to the rest of the conns in the queue? If no new SYN
	 * arrives for hours, no softIRQ  will be delivered,
	 * and the connections will just sit in the queue.
	 */

	for (;;) {
		err = o2net_accept_one(sock, &more);
		if (!more)
			break;
		cond_resched();
	}
}