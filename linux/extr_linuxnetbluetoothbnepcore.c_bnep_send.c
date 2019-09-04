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
struct kvec {void* member_0; size_t member_1; } ;
struct bnep_session {int /*<<< orphan*/  msg; struct socket* sock; } ;

/* Variables and functions */
 int kernel_sendmsg (struct socket*,int /*<<< orphan*/ *,struct kvec*,int,size_t) ; 

__attribute__((used)) static int bnep_send(struct bnep_session *s, void *data, size_t len)
{
	struct socket *sock = s->sock;
	struct kvec iv = { data, len };

	return kernel_sendmsg(sock, &s->msg, &iv, 1, len);
}