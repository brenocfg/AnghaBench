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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct l2cap_chan {struct sock* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_SK_SUSPEND ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void l2cap_sock_suspend_cb(struct l2cap_chan *chan)
{
	struct sock *sk = chan->data;

	set_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags);
	sk->sk_state_change(sk);
}