#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct file* file; TYPE_2__* sk; } ;
struct file {struct socket* private_data; } ;
struct TYPE_4__ {TYPE_1__* sk_prot_creator; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SOCK_INODE (struct socket*) ; 
 struct file* alloc_file_pseudo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_mnt ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  socket_file_ops ; 

struct file *sock_alloc_file(struct socket *sock, int flags, const char *dname)
{
	struct file *file;

	if (!dname)
		dname = sock->sk ? sock->sk->sk_prot_creator->name : "";

	file = alloc_file_pseudo(SOCK_INODE(sock), sock_mnt, dname,
				O_RDWR | (flags & O_NONBLOCK),
				&socket_file_ops);
	if (IS_ERR(file)) {
		sock_release(sock);
		return file;
	}

	sock->file = file;
	file->private_data = sock;
	return file;
}