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
struct socket {struct sock* sk; } ;
struct sockaddr_can {int /*<<< orphan*/  can_ifindex; int /*<<< orphan*/  can_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct raw_sock {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CAN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memset (struct sockaddr_can*,int /*<<< orphan*/ ,int) ; 
 struct raw_sock* raw_sk (struct sock*) ; 

__attribute__((used)) static int raw_getname(struct socket *sock, struct sockaddr *uaddr,
		       int peer)
{
	struct sockaddr_can *addr = (struct sockaddr_can *)uaddr;
	struct sock *sk = sock->sk;
	struct raw_sock *ro = raw_sk(sk);

	if (peer)
		return -EOPNOTSUPP;

	memset(addr, 0, sizeof(*addr));
	addr->can_family  = AF_CAN;
	addr->can_ifindex = ro->ifindex;

	return sizeof(*addr);
}