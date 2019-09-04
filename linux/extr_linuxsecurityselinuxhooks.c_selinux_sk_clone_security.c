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
struct sk_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  peer_sid; int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  selinux_netlbl_sk_security_reset (struct sk_security_struct*) ; 

__attribute__((used)) static void selinux_sk_clone_security(const struct sock *sk, struct sock *newsk)
{
	struct sk_security_struct *sksec = sk->sk_security;
	struct sk_security_struct *newsksec = newsk->sk_security;

	newsksec->sid = sksec->sid;
	newsksec->peer_sid = sksec->peer_sid;
	newsksec->sclass = sksec->sclass;

	selinux_netlbl_sk_security_reset(newsksec);
}