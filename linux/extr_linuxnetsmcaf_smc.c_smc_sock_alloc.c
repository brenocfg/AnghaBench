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
struct sock {int sk_protocol; TYPE_2__* sk_prot; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_lock; int /*<<< orphan*/  tx_work; } ;
struct smc_sock {int /*<<< orphan*/  clcsock_release_lock; TYPE_1__ conn; int /*<<< orphan*/  accept_q_lock; int /*<<< orphan*/  accept_q; int /*<<< orphan*/  connect_work; int /*<<< orphan*/  tcp_listen_work; } ;
struct proto {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_SMC ; 
 int SMCPROTO_SMC6 ; 
 int /*<<< orphan*/  SMC_INIT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  smc_connect_work ; 
 int /*<<< orphan*/  smc_destruct ; 
 struct proto smc_proto ; 
 struct proto smc_proto6 ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  smc_tcp_listen_work ; 
 int /*<<< orphan*/  smc_tx_work ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static struct sock *smc_sock_alloc(struct net *net, struct socket *sock,
				   int protocol)
{
	struct smc_sock *smc;
	struct proto *prot;
	struct sock *sk;

	prot = (protocol == SMCPROTO_SMC6) ? &smc_proto6 : &smc_proto;
	sk = sk_alloc(net, PF_SMC, GFP_KERNEL, prot, 0);
	if (!sk)
		return NULL;

	sock_init_data(sock, sk); /* sets sk_refcnt to 1 */
	sk->sk_state = SMC_INIT;
	sk->sk_destruct = smc_destruct;
	sk->sk_protocol = protocol;
	smc = smc_sk(sk);
	INIT_WORK(&smc->tcp_listen_work, smc_tcp_listen_work);
	INIT_WORK(&smc->connect_work, smc_connect_work);
	INIT_DELAYED_WORK(&smc->conn.tx_work, smc_tx_work);
	INIT_LIST_HEAD(&smc->accept_q);
	spin_lock_init(&smc->accept_q_lock);
	spin_lock_init(&smc->conn.send_lock);
	sk->sk_prot->hash(sk);
	sk_refcnt_debug_inc(sk);
	mutex_init(&smc->clcsock_release_lock);

	return sk;
}