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
struct sock {int /*<<< orphan*/  sk_ack_backlog; } ;
struct TYPE_2__ {struct sock* parent; int /*<<< orphan*/  accept_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct sock*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  bh_lock_sock_nested (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

void bt_accept_enqueue(struct sock *parent, struct sock *sk, bool bh)
{
	BT_DBG("parent %p, sk %p", parent, sk);

	sock_hold(sk);

	if (bh)
		bh_lock_sock_nested(sk);
	else
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	list_add_tail(&bt_sk(sk)->accept_q, &bt_sk(parent)->accept_q);
	bt_sk(sk)->parent = parent;

	if (bh)
		bh_unlock_sock(sk);
	else
		release_sock(sk);

	parent->sk_ack_backlog++;
}