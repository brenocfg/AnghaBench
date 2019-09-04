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
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int selinux_netlbl_socket_connect_locked (struct sock*,struct sockaddr*) ; 

int selinux_netlbl_socket_connect(struct sock *sk, struct sockaddr *addr)
{
	int rc;

	lock_sock(sk);
	rc = selinux_netlbl_socket_connect_locked(sk, addr);
	release_sock(sk);

	return rc;
}