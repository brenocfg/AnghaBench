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
struct udp_tunnel_sock_cfg {int /*<<< orphan*/  gro_complete; int /*<<< orphan*/  gro_receive; int /*<<< orphan*/  encap_destroy; int /*<<< orphan*/  encap_err_lookup; int /*<<< orphan*/  encap_rcv; int /*<<< orphan*/  encap_type; int /*<<< orphan*/  sk_user_data; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {scalar_t__ mc_loop; } ;
struct TYPE_3__ {int /*<<< orphan*/  gro_complete; int /*<<< orphan*/  gro_receive; int /*<<< orphan*/  encap_destroy; int /*<<< orphan*/  encap_err_lookup; int /*<<< orphan*/  encap_rcv; int /*<<< orphan*/  encap_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_inc_convert_csum (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udp_tunnel_encap_enable (struct socket*) ; 

void setup_udp_tunnel_sock(struct net *net, struct socket *sock,
			   struct udp_tunnel_sock_cfg *cfg)
{
	struct sock *sk = sock->sk;

	/* Disable multicast loopback */
	inet_sk(sk)->mc_loop = 0;

	/* Enable CHECKSUM_UNNECESSARY to CHECKSUM_COMPLETE conversion */
	inet_inc_convert_csum(sk);

	rcu_assign_sk_user_data(sk, cfg->sk_user_data);

	udp_sk(sk)->encap_type = cfg->encap_type;
	udp_sk(sk)->encap_rcv = cfg->encap_rcv;
	udp_sk(sk)->encap_err_lookup = cfg->encap_err_lookup;
	udp_sk(sk)->encap_destroy = cfg->encap_destroy;
	udp_sk(sk)->gro_receive = cfg->gro_receive;
	udp_sk(sk)->gro_complete = cfg->gro_complete;

	udp_tunnel_encap_enable(sock);
}