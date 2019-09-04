#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct socket {struct sock* sk; } ;
struct TYPE_10__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_5__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_protocol; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int const sclass; int /*<<< orphan*/  sid; } ;
struct TYPE_8__ {TYPE_5__ saddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  saddr; } ;
struct lsm_network_audit {TYPE_3__ v6info; TYPE_1__ v4info; scalar_t__ family; int /*<<< orphan*/  sport; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {struct lsm_network_audit* net; } ;
struct common_audit_data {TYPE_4__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
#define  AF_UNSPEC 132 
 int /*<<< orphan*/  DCCP_SOCKET__NODE_BIND ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NET ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  RAWIP_SOCKET__NODE_BIND ; 
 int /*<<< orphan*/  SCTP_SOCKET__NODE_BIND ; 
#define  SECCLASS_DCCP_SOCKET 131 
#define  SECCLASS_SCTP_SOCKET 130 
#define  SECCLASS_TCP_SOCKET 129 
#define  SECCLASS_UDP_SOCKET 128 
 int SIN6_LEN_RFC2133 ; 
 int /*<<< orphan*/  SOCKET__BIND ; 
 int /*<<< orphan*/  SOCKET__NAME_BIND ; 
 int /*<<< orphan*/  TCP_SOCKET__NODE_BIND ; 
 int /*<<< orphan*/  UDP_SOCKET__NODE_BIND ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  inet_get_local_port_range (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  inet_prot_sock (int /*<<< orphan*/ ) ; 
 unsigned short max (int /*<<< orphan*/ ,int) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int sel_netnode_sid (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int sel_netport_sid (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int sock_has_perm (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int selinux_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen)
{
	struct sock *sk = sock->sk;
	struct sk_security_struct *sksec = sk->sk_security;
	u16 family;
	int err;

	err = sock_has_perm(sk, SOCKET__BIND);
	if (err)
		goto out;

	/* If PF_INET or PF_INET6, check name_bind permission for the port. */
	family = sk->sk_family;
	if (family == PF_INET || family == PF_INET6) {
		char *addrp;
		struct common_audit_data ad;
		struct lsm_network_audit net = {0,};
		struct sockaddr_in *addr4 = NULL;
		struct sockaddr_in6 *addr6 = NULL;
		u16 family_sa = address->sa_family;
		unsigned short snum;
		u32 sid, node_perm;

		/*
		 * sctp_bindx(3) calls via selinux_sctp_bind_connect()
		 * that validates multiple binding addresses. Because of this
		 * need to check address->sa_family as it is possible to have
		 * sk->sk_family = PF_INET6 with addr->sa_family = AF_INET.
		 */
		switch (family_sa) {
		case AF_UNSPEC:
		case AF_INET:
			if (addrlen < sizeof(struct sockaddr_in))
				return -EINVAL;
			addr4 = (struct sockaddr_in *)address;
			if (family_sa == AF_UNSPEC) {
				/* see __inet_bind(), we only want to allow
				 * AF_UNSPEC if the address is INADDR_ANY
				 */
				if (addr4->sin_addr.s_addr != htonl(INADDR_ANY))
					goto err_af;
				family_sa = AF_INET;
			}
			snum = ntohs(addr4->sin_port);
			addrp = (char *)&addr4->sin_addr.s_addr;
			break;
		case AF_INET6:
			if (addrlen < SIN6_LEN_RFC2133)
				return -EINVAL;
			addr6 = (struct sockaddr_in6 *)address;
			snum = ntohs(addr6->sin6_port);
			addrp = (char *)&addr6->sin6_addr.s6_addr;
			break;
		default:
			goto err_af;
		}

		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->sport = htons(snum);
		ad.u.net->family = family_sa;

		if (snum) {
			int low, high;

			inet_get_local_port_range(sock_net(sk), &low, &high);

			if (snum < max(inet_prot_sock(sock_net(sk)), low) ||
			    snum > high) {
				err = sel_netport_sid(sk->sk_protocol,
						      snum, &sid);
				if (err)
					goto out;
				err = avc_has_perm(&selinux_state,
						   sksec->sid, sid,
						   sksec->sclass,
						   SOCKET__NAME_BIND, &ad);
				if (err)
					goto out;
			}
		}

		switch (sksec->sclass) {
		case SECCLASS_TCP_SOCKET:
			node_perm = TCP_SOCKET__NODE_BIND;
			break;

		case SECCLASS_UDP_SOCKET:
			node_perm = UDP_SOCKET__NODE_BIND;
			break;

		case SECCLASS_DCCP_SOCKET:
			node_perm = DCCP_SOCKET__NODE_BIND;
			break;

		case SECCLASS_SCTP_SOCKET:
			node_perm = SCTP_SOCKET__NODE_BIND;
			break;

		default:
			node_perm = RAWIP_SOCKET__NODE_BIND;
			break;
		}

		err = sel_netnode_sid(addrp, family_sa, &sid);
		if (err)
			goto out;

		if (family_sa == AF_INET)
			ad.u.net->v4info.saddr = addr4->sin_addr.s_addr;
		else
			ad.u.net->v6info.saddr = addr6->sin6_addr;

		err = avc_has_perm(&selinux_state,
				   sksec->sid, sid,
				   sksec->sclass, node_perm, &ad);
		if (err)
			goto out;
	}
out:
	return err;
err_af:
	/* Note that SCTP services expect -EINVAL, others -EAFNOSUPPORT. */
	if (sksec->sclass == SECCLASS_SCTP_SOCKET)
		return -EINVAL;
	return -EAFNOSUPPORT;
}