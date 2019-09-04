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
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sk_security_struct*) ; 
 int /*<<< orphan*/  selinux_netlbl_sk_security_free (struct sk_security_struct*) ; 

__attribute__((used)) static void selinux_sk_free_security(struct sock *sk)
{
	struct sk_security_struct *sksec = sk->sk_security;

	sk->sk_security = NULL;
	selinux_netlbl_sk_security_free(sksec);
	kfree(sksec);
}