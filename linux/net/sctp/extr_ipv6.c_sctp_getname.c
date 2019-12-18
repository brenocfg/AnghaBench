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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int inet6_getname (struct socket*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sctp_sk (int /*<<< orphan*/ ) ; 
 int sctp_v6_addr_to_user (int /*<<< orphan*/ ,union sctp_addr*) ; 

__attribute__((used)) static int sctp_getname(struct socket *sock, struct sockaddr *uaddr,
			int peer)
{
	int rc;

	rc = inet6_getname(sock, uaddr, peer);

	if (rc < 0)
		return rc;

	rc = sctp_v6_addr_to_user(sctp_sk(sock->sk),
					  (union sctp_addr *)uaddr);

	return rc;
}