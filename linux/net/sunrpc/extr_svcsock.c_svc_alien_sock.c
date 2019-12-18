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
struct net {int dummy; } ;

/* Variables and functions */
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

bool svc_alien_sock(struct net *net, int fd)
{
	int err;
	struct socket *sock = sockfd_lookup(fd, &err);
	bool ret = false;

	if (!sock)
		goto out;
	if (sock_net(sock->sk) != net)
		ret = true;
	sockfd_put(sock);
out:
	return ret;
}