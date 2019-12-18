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
struct msghdr {int /*<<< orphan*/  msg_iter; int /*<<< orphan*/ * member_0; } ;
struct kvec {char* member_0; size_t const member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,size_t const) ; 
 int sock_recvmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip_vs_receive(struct socket *sock, char *buffer, const size_t buflen)
{
	struct msghdr		msg = {NULL,};
	struct kvec		iov = {buffer, buflen};
	int			len;

	EnterFunction(7);

	/* Receive a packet */
	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, buflen);
	len = sock_recvmsg(sock, &msg, MSG_DONTWAIT);
	if (len < 0)
		return len;

	LeaveFunction(7);
	return len;
}