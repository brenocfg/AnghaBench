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
struct sock {int dummy; } ;
struct ipv6_txoptions {int opt_flen; int opt_nflen; } ;
struct ipv6_pinfo {int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct ipv6_txoptions* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int sctp_v6_ip_options_len(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_txoptions *opt;
	int len = 0;

	rcu_read_lock();
	opt = rcu_dereference(np->opt);
	if (opt)
		len = opt->opt_flen + opt->opt_nflen;

	rcu_read_unlock();
	return len;
}