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
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;
struct inet_sock {unsigned int cmsg_flags; } ;

/* Variables and functions */
 unsigned int IP_CMSG_CHECKSUM ; 
 unsigned int IP_CMSG_ORIGDSTADDR ; 
 unsigned int IP_CMSG_PASSSEC ; 
 unsigned int IP_CMSG_PKTINFO ; 
 unsigned int IP_CMSG_RECVFRAGSIZE ; 
 unsigned int IP_CMSG_RECVOPTS ; 
 unsigned int IP_CMSG_RETOPTS ; 
 unsigned int IP_CMSG_TOS ; 
 unsigned int IP_CMSG_TTL ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_checksum (struct msghdr*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  ip_cmsg_recv_dstaddr (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_fragsize (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_opts (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_pktinfo (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_retopts (int /*<<< orphan*/ ,struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_security (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_tos (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_cmsg_recv_ttl (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

void ip_cmsg_recv_offset(struct msghdr *msg, struct sock *sk,
			 struct sk_buff *skb, int tlen, int offset)
{
	struct inet_sock *inet = inet_sk(sk);
	unsigned int flags = inet->cmsg_flags;

	/* Ordered by supposed usage frequency */
	if (flags & IP_CMSG_PKTINFO) {
		ip_cmsg_recv_pktinfo(msg, skb);

		flags &= ~IP_CMSG_PKTINFO;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_TTL) {
		ip_cmsg_recv_ttl(msg, skb);

		flags &= ~IP_CMSG_TTL;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_TOS) {
		ip_cmsg_recv_tos(msg, skb);

		flags &= ~IP_CMSG_TOS;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_RECVOPTS) {
		ip_cmsg_recv_opts(msg, skb);

		flags &= ~IP_CMSG_RECVOPTS;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_RETOPTS) {
		ip_cmsg_recv_retopts(sock_net(sk), msg, skb);

		flags &= ~IP_CMSG_RETOPTS;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_PASSSEC) {
		ip_cmsg_recv_security(msg, skb);

		flags &= ~IP_CMSG_PASSSEC;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_ORIGDSTADDR) {
		ip_cmsg_recv_dstaddr(msg, skb);

		flags &= ~IP_CMSG_ORIGDSTADDR;
		if (!flags)
			return;
	}

	if (flags & IP_CMSG_CHECKSUM)
		ip_cmsg_recv_checksum(msg, skb, tlen, offset);

	if (flags & IP_CMSG_RECVFRAGSIZE)
		ip_cmsg_recv_fragsize(msg, skb);
}