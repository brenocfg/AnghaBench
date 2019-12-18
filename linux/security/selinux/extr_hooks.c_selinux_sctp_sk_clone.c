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
struct sctp_endpoint {int /*<<< orphan*/  peer_secid; int /*<<< orphan*/  secid; } ;

/* Variables and functions */
 int /*<<< orphan*/  selinux_netlbl_sctp_sk_clone (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  selinux_policycap_extsockclass () ; 
 void selinux_sk_clone_security (struct sock*,struct sock*) ; 

__attribute__((used)) static void selinux_sctp_sk_clone(struct sctp_endpoint *ep, struct sock *sk,
				  struct sock *newsk)
{
	struct sk_security_struct *sksec = sk->sk_security;
	struct sk_security_struct *newsksec = newsk->sk_security;

	/* If policy does not support SECCLASS_SCTP_SOCKET then call
	 * the non-sctp clone version.
	 */
	if (!selinux_policycap_extsockclass())
		return selinux_sk_clone_security(sk, newsk);

	newsksec->sid = ep->secid;
	newsksec->peer_sid = ep->peer_secid;
	newsksec->sclass = sksec->sclass;
	selinux_netlbl_sctp_sk_clone(sk, newsk);
}