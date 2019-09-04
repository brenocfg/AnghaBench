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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;
struct smc_sock {int /*<<< orphan*/  clcsock; scalar_t__ use_fallback; } ;
struct page {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EPIPE ; 
 scalar_t__ SMC_ACTIVE ; 
 int kernel_sendpage (int /*<<< orphan*/ ,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int sock_no_sendpage (struct socket*,struct page*,int,size_t,int) ; 

__attribute__((used)) static ssize_t smc_sendpage(struct socket *sock, struct page *page,
			    int offset, size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct smc_sock *smc;
	int rc = -EPIPE;

	smc = smc_sk(sk);
	lock_sock(sk);
	if (sk->sk_state != SMC_ACTIVE) {
		release_sock(sk);
		goto out;
	}
	release_sock(sk);
	if (smc->use_fallback)
		rc = kernel_sendpage(smc->clcsock, page, offset,
				     size, flags);
	else
		rc = sock_no_sendpage(sock, page, offset, size, flags);

out:
	return rc;
}