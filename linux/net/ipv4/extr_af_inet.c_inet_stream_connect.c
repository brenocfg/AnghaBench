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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int __inet_stream_connect (struct socket*,struct sockaddr*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ ) ; 

int inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			int addr_len, int flags)
{
	int err;

	lock_sock(sock->sk);
	err = __inet_stream_connect(sock, uaddr, addr_len, flags, 0);
	release_sock(sock->sk);
	return err;
}