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
struct sock {int dummy; } ;
struct sco_conn {struct sock* sk; } ;
struct TYPE_2__ {struct sco_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sco_conn*) ; 
 int /*<<< orphan*/  bt_accept_enqueue (struct sock*,struct sock*,int) ; 
 TYPE_1__* sco_pi (struct sock*) ; 

__attribute__((used)) static void __sco_chan_add(struct sco_conn *conn, struct sock *sk,
			   struct sock *parent)
{
	BT_DBG("conn %p", conn);

	sco_pi(sk)->conn = conn;
	conn->sk = sk;

	if (parent)
		bt_accept_enqueue(parent, sk, true);
}