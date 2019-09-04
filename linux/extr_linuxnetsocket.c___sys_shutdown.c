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
struct socket {int /*<<< orphan*/  file; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* shutdown ) (struct socket*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fput_light (int /*<<< orphan*/ ,int) ; 
 int security_socket_shutdown (struct socket*,int) ; 
 struct socket* sockfd_lookup_light (int,int*,int*) ; 
 int stub1 (struct socket*,int) ; 

int __sys_shutdown(int fd, int how)
{
	int err, fput_needed;
	struct socket *sock;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	if (sock != NULL) {
		err = security_socket_shutdown(sock, how);
		if (!err)
			err = sock->ops->shutdown(sock, how);
		fput_light(sock->file, fput_needed);
	}
	return err;
}