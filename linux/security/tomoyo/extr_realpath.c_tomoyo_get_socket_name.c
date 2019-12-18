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
struct sock {int sk_family; int sk_type; int sk_protocol; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct socket* SOCKET_I (struct inode*) ; 
 struct inode* d_backing_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char* const,int const,char*,...) ; 

__attribute__((used)) static char *tomoyo_get_socket_name(const struct path *path, char * const buffer,
				    const int buflen)
{
	struct inode *inode = d_backing_inode(path->dentry);
	struct socket *sock = inode ? SOCKET_I(inode) : NULL;
	struct sock *sk = sock ? sock->sk : NULL;

	if (sk) {
		snprintf(buffer, buflen, "socket:[family=%u:type=%u:protocol=%u]",
			 sk->sk_family, sk->sk_type, sk->sk_protocol);
	} else {
		snprintf(buffer, buflen, "socket:[unknown]");
	}
	return buffer;
}