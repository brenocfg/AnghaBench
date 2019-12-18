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
struct socket {int dummy; } ;
struct sock_xprt {scalar_t__ srcport; } ;

/* Variables and functions */
 scalar_t__ xs_sock_getport (struct socket*) ; 

__attribute__((used)) static void xs_set_srcport(struct sock_xprt *transport, struct socket *sock)
{
	if (transport->srcport == 0)
		transport->srcport = xs_sock_getport(sock);
}