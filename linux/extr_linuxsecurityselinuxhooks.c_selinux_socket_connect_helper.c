#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct socket {struct sock* sk; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
struct sock {int /*<<< orphan*/  sk_protocol; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int sclass; int /*<<< orphan*/  sid; } ;
struct lsm_network_audit {int family; int /*<<< orphan*/  dport; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {struct lsm_network_audit* net; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
 int /*<<< orphan*/  DCCP_SOCKET__NAME_CONNECT ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NET ; 
 int /*<<< orphan*/  SCTP_SOCKET__NAME_CONNECT ; 
#define  SECCLASS_DCCP_SOCKET 130 
#define  SECCLASS_SCTP_SOCKET 129 
#define  SECCLASS_TCP_SOCKET 128 
 int SIN6_LEN_RFC2133 ; 
 int /*<<< orphan*/  SOCKET__CONNECT ; 
 int /*<<< orphan*/  TCP_SOCKET__NAME_CONNECT ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int sel_netport_sid (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int sock_has_perm (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_socket_connect_helper(struct socket *sock,
					 struct sockaddr *address, int addrlen)
{
	struct sock *sk = sock->sk;
	struct sk_security_struct *sksec = sk->sk_security;
	int err;

	err = sock_has_perm(sk, SOCKET__CONNECT);
	if (err)
		return err;

	/*
	 * If a TCP, DCCP or SCTP socket, check name_connect permission
	 * for the port.
	 */
	if (sksec->sclass == SECCLASS_TCP_SOCKET ||
	    sksec->sclass == SECCLASS_DCCP_SOCKET ||
	    sksec->sclass == SECCLASS_SCTP_SOCKET) {
		struct common_audit_data ad;
		struct lsm_network_audit net = {0,};
		struct sockaddr_in *addr4 = NULL;
		struct sockaddr_in6 *addr6 = NULL;
		unsigned short snum;
		u32 sid, perm;

		/* sctp_connectx(3) calls via selinux_sctp_bind_connect()
		 * that validates multiple connect addresses. Because of this
		 * need to check address->sa_family as it is possible to have
		 * sk->sk_family = PF_INET6 with addr->sa_family = AF_INET.
		 */
		switch (address->sa_family) {
		case AF_INET:
			addr4 = (struct sockaddr_in *)address;
			if (addrlen < sizeof(struct sockaddr_in))
				return -EINVAL;
			snum = ntohs(addr4->sin_port);
			break;
		case AF_INET6:
			addr6 = (struct sockaddr_in6 *)address;
			if (addrlen < SIN6_LEN_RFC2133)
				return -EINVAL;
			snum = ntohs(addr6->sin6_port);
			break;
		default:
			/* Note that SCTP services expect -EINVAL, whereas
			 * others expect -EAFNOSUPPORT.
			 */
			if (sksec->sclass == SECCLASS_SCTP_SOCKET)
				return -EINVAL;
			else
				return -EAFNOSUPPORT;
		}

		err = sel_netport_sid(sk->sk_protocol, snum, &sid);
		if (err)
			return err;

		switch (sksec->sclass) {
		case SECCLASS_TCP_SOCKET:
			perm = TCP_SOCKET__NAME_CONNECT;
			break;
		case SECCLASS_DCCP_SOCKET:
			perm = DCCP_SOCKET__NAME_CONNECT;
			break;
		case SECCLASS_SCTP_SOCKET:
			perm = SCTP_SOCKET__NAME_CONNECT;
			break;
		}

		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->dport = htons(snum);
		ad.u.net->family = address->sa_family;
		err = avc_has_perm(&selinux_state,
				   sksec->sid, sid, sksec->sclass, perm, &ad);
		if (err)
			return err;
	}

	return 0;
}