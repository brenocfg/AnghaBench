#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_family; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ AF_NETLINK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSOCK ; 
 struct sock* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* SOCKET_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

struct sock *netlink_getsockbyfilp(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	struct sock *sock;

	if (!S_ISSOCK(inode->i_mode))
		return ERR_PTR(-ENOTSOCK);

	sock = SOCKET_I(inode)->sk;
	if (sock->sk_family != AF_NETLINK)
		return ERR_PTR(-EINVAL);

	sock_hold(sock);
	return sock;
}