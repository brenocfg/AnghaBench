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
typedef  scalar_t__ u16 ;
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  nlbl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLBL_LABELED ; 
 int /*<<< orphan*/  NLBL_UNSET ; 
 scalar_t__ PF_INET ; 

void selinux_netlbl_inet_csk_clone(struct sock *sk, u16 family)
{
	struct sk_security_struct *sksec = sk->sk_security;

	if (family == PF_INET)
		sksec->nlbl_state = NLBL_LABELED;
	else
		sksec->nlbl_state = NLBL_UNSET;
}