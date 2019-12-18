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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_SEND ; 
 int /*<<< orphan*/  OP_SENDMSG ; 
 int aa_sock_msg_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket*,struct msghdr*,int) ; 

__attribute__((used)) static int apparmor_socket_sendmsg(struct socket *sock,
				   struct msghdr *msg, int size)
{
	return aa_sock_msg_perm(OP_SENDMSG, AA_MAY_SEND, sock, msg, size);
}