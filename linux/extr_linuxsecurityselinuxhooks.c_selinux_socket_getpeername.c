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

/* Variables and functions */
 int /*<<< orphan*/  SOCKET__GETATTR ; 
 int sock_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_socket_getpeername(struct socket *sock)
{
	return sock_has_perm(sock->sk, SOCKET__GETATTR);
}