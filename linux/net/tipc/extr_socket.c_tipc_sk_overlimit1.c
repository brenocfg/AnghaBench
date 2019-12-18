#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int len; } ;
struct sock {TYPE_1__ sk_backlog; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_4__ {int /*<<< orphan*/  dupl_rcvcnt; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int rcvbuf_limit (struct sock*,struct sk_buff*) ; 
 unsigned int sk_rmem_alloc_get (struct sock*) ; 
 TYPE_2__* tipc_sk (struct sock*) ; 

bool tipc_sk_overlimit1(struct sock *sk, struct sk_buff *skb)
{
	atomic_t *dcnt = &tipc_sk(sk)->dupl_rcvcnt;
	unsigned int lim = rcvbuf_limit(sk, skb) + atomic_read(dcnt);
	unsigned int qsize = sk->sk_backlog.len + sk_rmem_alloc_get(sk);

	return (qsize > lim * 90 / 100);
}