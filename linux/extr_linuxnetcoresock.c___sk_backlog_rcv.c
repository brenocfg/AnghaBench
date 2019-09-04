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
struct sock {int (* sk_backlog_rcv ) (struct sock*,struct sk_buff*) ;} ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SOCK_MEMALLOC ; 
 int /*<<< orphan*/  memalloc_noreclaim_restore (unsigned int) ; 
 unsigned int memalloc_noreclaim_save () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int stub1 (struct sock*,struct sk_buff*) ; 

int __sk_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	int ret;
	unsigned int noreclaim_flag;

	/* these should have been dropped before queueing */
	BUG_ON(!sock_flag(sk, SOCK_MEMALLOC));

	noreclaim_flag = memalloc_noreclaim_save();
	ret = sk->sk_backlog_rcv(sk, skb);
	memalloc_noreclaim_restore(noreclaim_flag);

	return ret;
}