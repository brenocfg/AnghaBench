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
struct socket {int /*<<< orphan*/  sk; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {int (* dgram_dequeue ) (int /*<<< orphan*/ ,struct msghdr*,size_t,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct msghdr*,size_t,int) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsock_dgram_recvmsg(struct socket *sock, struct msghdr *msg,
			       size_t len, int flags)
{
	return transport->dgram_dequeue(vsock_sk(sock->sk), msg, len, flags);
}