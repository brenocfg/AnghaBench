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
struct sockaddr_can {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct j1939_sock {int state; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int J1939_MIN_NAMELEN ; 
 int J1939_SOCK_CONNECTED ; 
 struct j1939_sock* j1939_sk (struct sock*) ; 
 int /*<<< orphan*/  j1939_sk_sock2sockaddr_can (struct sockaddr_can*,struct j1939_sock*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int j1939_sk_getname(struct socket *sock, struct sockaddr *uaddr,
			    int peer)
{
	struct sockaddr_can *addr = (struct sockaddr_can *)uaddr;
	struct sock *sk = sock->sk;
	struct j1939_sock *jsk = j1939_sk(sk);
	int ret = 0;

	lock_sock(sk);

	if (peer && !(jsk->state & J1939_SOCK_CONNECTED)) {
		ret = -EADDRNOTAVAIL;
		goto failure;
	}

	j1939_sk_sock2sockaddr_can(addr, jsk, peer);
	ret = J1939_MIN_NAMELEN;

 failure:
	release_sock(sk);

	return ret;
}