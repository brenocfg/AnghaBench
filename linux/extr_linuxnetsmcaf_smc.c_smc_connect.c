#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {int sk_state; } ;
struct smc_sock {TYPE_3__* clcsock; int /*<<< orphan*/  connect_work; TYPE_2__* connect_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {int alen; int flags; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int syn_smc; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EALREADY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_NONBLOCK ; 
#define  SMC_ACTIVE 129 
#define  SMC_INIT 128 
 int __smc_connect (struct smc_sock*) ; 
 int kernel_connect (TYPE_3__*,struct sockaddr*,int,int) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 TYPE_1__* tcp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_connect(struct socket *sock, struct sockaddr *addr,
		       int alen, int flags)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = -EINVAL;

	smc = smc_sk(sk);

	/* separate smc parameter checking to be safe */
	if (alen < sizeof(addr->sa_family))
		goto out_err;
	if (addr->sa_family != AF_INET && addr->sa_family != AF_INET6)
		goto out_err;

	lock_sock(sk);
	switch (sk->sk_state) {
	default:
		goto out;
	case SMC_ACTIVE:
		rc = -EISCONN;
		goto out;
	case SMC_INIT:
		rc = 0;
		break;
	}

	smc_copy_sock_settings_to_clc(smc);
	tcp_sk(smc->clcsock->sk)->syn_smc = 1;
	if (flags & O_NONBLOCK) {
		if (smc->connect_info) {
			rc = -EALREADY;
			goto out;
		}
		smc->connect_info = kzalloc(alen + 2 * sizeof(int), GFP_KERNEL);
		if (!smc->connect_info) {
			rc = -ENOMEM;
			goto out;
		}
		smc->connect_info->alen = alen;
		smc->connect_info->flags = flags ^ O_NONBLOCK;
		memcpy(&smc->connect_info->addr, addr, alen);
		schedule_work(&smc->connect_work);
		rc = -EINPROGRESS;
	} else {
		rc = kernel_connect(smc->clcsock, addr, alen, flags);
		if (rc)
			goto out;

		rc = __smc_connect(smc);
		if (rc < 0)
			goto out;
		else
			rc = 0; /* success cases including fallback */
	}

out:
	release_sock(sk);
out_err:
	return rc;
}