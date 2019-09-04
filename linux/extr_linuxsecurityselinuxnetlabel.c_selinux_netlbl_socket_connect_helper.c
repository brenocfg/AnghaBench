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
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  nlbl_state; } ;
struct netlbl_lsm_secattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NLBL_CONNLABELED ; 
 int /*<<< orphan*/  NLBL_REQSKB ; 
 int netlbl_conn_setattr (struct sock*,struct sockaddr*,struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_sock_delattr (struct sock*) ; 
 struct netlbl_lsm_secattr* selinux_netlbl_sock_genattr (struct sock*) ; 

__attribute__((used)) static int selinux_netlbl_socket_connect_helper(struct sock *sk,
						struct sockaddr *addr)
{
	int rc;
	struct sk_security_struct *sksec = sk->sk_security;
	struct netlbl_lsm_secattr *secattr;

	/* connected sockets are allowed to disconnect when the address family
	 * is set to AF_UNSPEC, if that is what is happening we want to reset
	 * the socket */
	if (addr->sa_family == AF_UNSPEC) {
		netlbl_sock_delattr(sk);
		sksec->nlbl_state = NLBL_REQSKB;
		rc = 0;
		return rc;
	}
	secattr = selinux_netlbl_sock_genattr(sk);
	if (secattr == NULL) {
		rc = -ENOMEM;
		return rc;
	}
	rc = netlbl_conn_setattr(sk, addr, secattr);
	if (rc == 0)
		sksec->nlbl_state = NLBL_CONNLABELED;

	return rc;
}