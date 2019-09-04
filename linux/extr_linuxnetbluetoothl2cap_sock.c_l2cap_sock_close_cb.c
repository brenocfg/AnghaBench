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
struct l2cap_chan {struct sock* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 

__attribute__((used)) static void l2cap_sock_close_cb(struct l2cap_chan *chan)
{
	struct sock *sk = chan->data;

	l2cap_sock_kill(sk);
}