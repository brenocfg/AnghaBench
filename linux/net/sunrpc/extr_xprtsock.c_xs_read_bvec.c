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
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct bio_vec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_bvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bio_vec*,unsigned long,size_t) ; 
 int /*<<< orphan*/  xs_sock_recvmsg (struct socket*,struct msghdr*,int,size_t) ; 

__attribute__((used)) static ssize_t
xs_read_bvec(struct socket *sock, struct msghdr *msg, int flags,
		struct bio_vec *bvec, unsigned long nr, size_t count,
		size_t seek)
{
	iov_iter_bvec(&msg->msg_iter, READ, bvec, nr, count);
	return xs_sock_recvmsg(sock, msg, flags, seek);
}