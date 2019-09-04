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
struct iucv_sock {struct sock* parent; int /*<<< orphan*/  accept_q_lock; int /*<<< orphan*/  accept_q; } ;

/* Variables and functions */
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_acceptq_removed (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void iucv_accept_unlink(struct sock *sk)
{
	unsigned long flags;
	struct iucv_sock *par = iucv_sk(iucv_sk(sk)->parent);

	spin_lock_irqsave(&par->accept_q_lock, flags);
	list_del_init(&iucv_sk(sk)->accept_q);
	spin_unlock_irqrestore(&par->accept_q_lock, flags);
	sk_acceptq_removed(iucv_sk(sk)->parent);
	iucv_sk(sk)->parent = NULL;
	sock_put(sk);
}