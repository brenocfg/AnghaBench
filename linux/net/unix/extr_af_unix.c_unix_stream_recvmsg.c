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
struct unix_stream_read_state {size_t size; int flags; struct msghdr* msg; struct socket* socket; int /*<<< orphan*/  recv_actor; } ;
struct socket {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unix_stream_read_actor ; 
 int unix_stream_read_generic (struct unix_stream_read_state*,int) ; 

__attribute__((used)) static int unix_stream_recvmsg(struct socket *sock, struct msghdr *msg,
			       size_t size, int flags)
{
	struct unix_stream_read_state state = {
		.recv_actor = unix_stream_read_actor,
		.socket = sock,
		.msg = msg,
		.size = size,
		.flags = flags
	};

	return unix_stream_read_generic(&state, true);
}