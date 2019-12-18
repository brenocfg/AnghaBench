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
struct kvec {int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int /*<<< orphan*/ ) ; 
 int xs_sendmsg (struct socket*,struct msghdr*,size_t) ; 

__attribute__((used)) static int xs_send_kvec(struct socket *sock, struct msghdr *msg, struct kvec *vec, size_t seek)
{
	iov_iter_kvec(&msg->msg_iter, WRITE, vec, 1, vec->iov_len);
	return xs_sendmsg(sock, msg, seek);
}