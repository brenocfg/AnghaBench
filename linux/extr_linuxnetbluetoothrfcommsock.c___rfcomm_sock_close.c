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
struct sock {int sk_state; int /*<<< orphan*/  sk_socket; } ;
struct rfcomm_dlc {int dummy; } ;
struct TYPE_2__ {struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
#define  BT_CONFIG 132 
#define  BT_CONNECT 131 
#define  BT_CONNECT2 130 
#define  BT_CONNECTED 129 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int,int /*<<< orphan*/ ) ; 
#define  BT_LISTEN 128 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  rfcomm_dlc_close (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_sock_cleanup_listen (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rfcomm_sock_close(struct sock *sk)
{
	struct rfcomm_dlc *d = rfcomm_pi(sk)->dlc;

	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	switch (sk->sk_state) {
	case BT_LISTEN:
		rfcomm_sock_cleanup_listen(sk);
		break;

	case BT_CONNECT:
	case BT_CONNECT2:
	case BT_CONFIG:
	case BT_CONNECTED:
		rfcomm_dlc_close(d, 0);
		/* fall through */

	default:
		sock_set_flag(sk, SOCK_ZAPPED);
		break;
	}
}