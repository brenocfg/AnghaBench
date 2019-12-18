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
struct sock {int dummy; } ;
struct smc_sock {TYPE_2__* clcsock; } ;
struct TYPE_6__ {TYPE_1__* sk_prot; } ;
struct TYPE_5__ {TYPE_3__* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* keepalive ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static void smc_set_keepalive(struct sock *sk, int val)
{
	struct smc_sock *smc = smc_sk(sk);

	smc->clcsock->sk->sk_prot->keepalive(smc->clcsock->sk, val);
}