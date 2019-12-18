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
struct sock_xprt {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int xs_poll_socket (struct sock_xprt*) ; 

__attribute__((used)) static bool xs_poll_socket_readable(struct sock_xprt *transport)
{
	__poll_t events = xs_poll_socket(transport);

	return (events & (EPOLLIN | EPOLLRDNORM)) && !(events & EPOLLRDHUP);
}