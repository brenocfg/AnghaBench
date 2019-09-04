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
struct sockaddr_dn {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct dn_scp {int state; } ;

/* Variables and functions */
#define  DN_CC 132 
#define  DN_CI 131 
#define  DN_CR 130 
#define  DN_O 129 
#define  DN_RUN 128 
 struct dn_scp* DN_SK (struct sock*) ; 
 int EINVAL ; 
 int __dn_connect (struct sock*,struct sockaddr_dn*,int,long*,int) ; 
 int dn_confirm_accept (struct sock*,long*,int /*<<< orphan*/ ) ; 
 int dn_wait_run (struct sock*,long*) ; 

__attribute__((used)) static inline int dn_check_state(struct sock *sk, struct sockaddr_dn *addr, int addrlen, long *timeo, int flags)
{
	struct dn_scp *scp = DN_SK(sk);

	switch (scp->state) {
	case DN_RUN:
		return 0;
	case DN_CR:
		return dn_confirm_accept(sk, timeo, sk->sk_allocation);
	case DN_CI:
	case DN_CC:
		return dn_wait_run(sk, timeo);
	case DN_O:
		return __dn_connect(sk, addr, addrlen, timeo, flags);
	}

	return -EINVAL;
}