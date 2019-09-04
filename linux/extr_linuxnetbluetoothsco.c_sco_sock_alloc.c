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
struct socket {int dummy; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_destruct; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  accept_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  BT_VOICE_CVSD_16BIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SCO_CONN_TIMEOUT ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  bt_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 TYPE_1__* sco_pi (struct sock*) ; 
 int /*<<< orphan*/  sco_proto ; 
 int /*<<< orphan*/  sco_sk_list ; 
 int /*<<< orphan*/  sco_sock_destruct ; 
 int /*<<< orphan*/  sco_sock_timeout ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock *sco_sock_alloc(struct net *net, struct socket *sock,
				   int proto, gfp_t prio, int kern)
{
	struct sock *sk;

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &sco_proto, kern);
	if (!sk)
		return NULL;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	sk->sk_destruct = sco_sock_destruct;
	sk->sk_sndtimeo = SCO_CONN_TIMEOUT;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state    = BT_OPEN;

	sco_pi(sk)->setting = BT_VOICE_CVSD_16BIT;

	timer_setup(&sk->sk_timer, sco_sock_timeout, 0);

	bt_sock_link(&sco_sk_list, sk);
	return sk;
}