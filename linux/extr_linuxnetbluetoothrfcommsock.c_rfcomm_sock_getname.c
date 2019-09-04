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
struct socket {struct sock* sk; } ;
struct sockaddr_rc {int /*<<< orphan*/  rc_bdaddr; int /*<<< orphan*/  rc_channel; int /*<<< orphan*/  rc_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECT2 ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rc*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 

__attribute__((used)) static int rfcomm_sock_getname(struct socket *sock, struct sockaddr *addr, int peer)
{
	struct sockaddr_rc *sa = (struct sockaddr_rc *) addr;
	struct sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (peer && sk->sk_state != BT_CONNECTED &&
	    sk->sk_state != BT_CONNECT && sk->sk_state != BT_CONNECT2)
		return -ENOTCONN;

	memset(sa, 0, sizeof(*sa));
	sa->rc_family  = AF_BLUETOOTH;
	sa->rc_channel = rfcomm_pi(sk)->channel;
	if (peer)
		bacpy(&sa->rc_bdaddr, &rfcomm_pi(sk)->dst);
	else
		bacpy(&sa->rc_bdaddr, &rfcomm_pi(sk)->src);

	return sizeof(struct sockaddr_rc);
}