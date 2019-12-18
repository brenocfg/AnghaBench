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
struct socket {TYPE_1__* ops; struct sock* sk; } ;
struct sock {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; } ;
struct TYPE_2__ {scalar_t__ family; } ;

/* Variables and functions */
 int FMODE_PATH ; 
 scalar_t__ PF_UNIX ; 
 struct socket* SOCKET_I (struct inode*) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 struct sock* io_uring_get_socket (struct file*) ; 

struct sock *unix_get_socket(struct file *filp)
{
	struct sock *u_sock = NULL;
	struct inode *inode = file_inode(filp);

	/* Socket ? */
	if (S_ISSOCK(inode->i_mode) && !(filp->f_mode & FMODE_PATH)) {
		struct socket *sock = SOCKET_I(inode);
		struct sock *s = sock->sk;

		/* PF_UNIX ? */
		if (s && sock->ops && sock->ops->family == PF_UNIX)
			u_sock = s;
	} else {
		/* Could be an io_uring instance */
		u_sock = io_uring_get_socket(filp);
	}
	return u_sock;
}