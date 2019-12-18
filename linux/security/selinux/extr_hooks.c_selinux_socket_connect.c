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
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int selinux_netlbl_socket_connect (struct sock*,struct sockaddr*) ; 
 int selinux_socket_connect_helper (struct socket*,struct sockaddr*,int) ; 

__attribute__((used)) static int selinux_socket_connect(struct socket *sock,
				  struct sockaddr *address, int addrlen)
{
	int err;
	struct sock *sk = sock->sk;

	err = selinux_socket_connect_helper(sock, address, addrlen);
	if (err)
		return err;

	return selinux_netlbl_socket_connect(sk, address);
}