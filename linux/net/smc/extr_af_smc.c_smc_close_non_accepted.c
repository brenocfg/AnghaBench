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
struct sock {scalar_t__ sk_lingertime; } ;
struct smc_sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ SMC_MAX_STREAM_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  __smc_release (struct smc_sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void smc_close_non_accepted(struct sock *sk)
{
	struct smc_sock *smc = smc_sk(sk);

	lock_sock(sk);
	if (!sk->sk_lingertime)
		/* wait for peer closing */
		sk->sk_lingertime = SMC_MAX_STREAM_WAIT_TIMEOUT;
	__smc_release(smc);
	release_sock(sk);
	sock_put(sk); /* final sock_put */
}