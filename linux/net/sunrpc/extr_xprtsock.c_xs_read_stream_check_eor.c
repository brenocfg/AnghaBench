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
struct sock_xprt {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_EOR ; 
 scalar_t__ xs_read_stream_request_done (struct sock_xprt*) ; 

__attribute__((used)) static void
xs_read_stream_check_eor(struct sock_xprt *transport,
		struct msghdr *msg)
{
	if (xs_read_stream_request_done(transport))
		msg->msg_flags |= MSG_EOR;
}