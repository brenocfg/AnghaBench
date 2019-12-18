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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;
struct smc_sock {TYPE_2__* clcsock; scalar_t__ use_fallback; int /*<<< orphan*/  fallback_rsn; int /*<<< orphan*/  connect_nonblock; } ;
struct msghdr {int msg_flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* sendmsg ) (TYPE_2__*,struct msghdr*,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int MSG_FASTOPEN ; 
 scalar_t__ SMC_ACTIVE ; 
 scalar_t__ SMC_APPCLOSEWAIT1 ; 
 int /*<<< orphan*/  SMC_CLC_DECL_OPTUNSUPP ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  smc_switch_to_fallback (struct smc_sock*) ; 
 int smc_tx_sendmsg (struct smc_sock*,struct msghdr*,size_t) ; 
 int stub1 (TYPE_2__*,struct msghdr*,size_t) ; 

__attribute__((used)) static int smc_sendmsg(struct socket *sock, struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = -EPIPE;

	smc = smc_sk(sk);
	lock_sock(sk);
	if ((sk->sk_state != SMC_ACTIVE) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT1) &&
	    (sk->sk_state != SMC_INIT))
		goto out;

	if (msg->msg_flags & MSG_FASTOPEN) {
		if (sk->sk_state == SMC_INIT && !smc->connect_nonblock) {
			smc_switch_to_fallback(smc);
			smc->fallback_rsn = SMC_CLC_DECL_OPTUNSUPP;
		} else {
			rc = -EINVAL;
			goto out;
		}
	}

	if (smc->use_fallback)
		rc = smc->clcsock->ops->sendmsg(smc->clcsock, msg, len);
	else
		rc = smc_tx_sendmsg(smc, msg, len);
out:
	release_sock(sk);
	return rc;
}