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
struct j1939_sock {int /*<<< orphan*/  waitq; int /*<<< orphan*/  skb_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 struct j1939_sock* j1939_sk (struct sock*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void j1939_sock_pending_del(struct sock *sk)
{
	struct j1939_sock *jsk = j1939_sk(sk);

	/* atomic_dec_return returns the new value */
	if (!atomic_dec_return(&jsk->skb_pending))
		wake_up(&jsk->waitq);	/* no pending SKB's */
}