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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int sctp_connect (int /*<<< orphan*/ ,struct sockaddr*,int,int) ; 

int sctp_inet_connect(struct socket *sock, struct sockaddr *uaddr,
		      int addr_len, int flags)
{
	if (addr_len < sizeof(uaddr->sa_family))
		return -EINVAL;

	if (uaddr->sa_family == AF_UNSPEC)
		return -EOPNOTSUPP;

	return sctp_connect(sock->sk, uaddr, addr_len, flags);
}