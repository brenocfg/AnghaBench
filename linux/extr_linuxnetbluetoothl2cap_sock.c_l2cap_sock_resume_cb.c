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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;void* sk_state; } ;
struct l2cap_chan {void* state; int /*<<< orphan*/  flags; struct sock* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* BT_CONNECTED ; 
 int /*<<< orphan*/  BT_SK_SUSPEND ; 
 int /*<<< orphan*/  FLAG_PENDING_SECURITY ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_sock_resume_cb(struct l2cap_chan *chan)
{
	struct sock *sk = chan->data;

	if (test_and_clear_bit(FLAG_PENDING_SECURITY, &chan->flags)) {
		sk->sk_state = BT_CONNECTED;
		chan->state = BT_CONNECTED;
	}

	clear_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags);
	sk->sk_state_change(sk);
}