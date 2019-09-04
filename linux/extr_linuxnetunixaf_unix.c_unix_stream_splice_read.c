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
struct unix_stream_read_state {size_t size; unsigned int splice_flags; int /*<<< orphan*/  flags; struct pipe_inode_info* pipe; struct socket* socket; int /*<<< orphan*/  recv_actor; } ;
struct socket {TYPE_1__* file; } ;
struct pipe_inode_info {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPIPE ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int O_NONBLOCK ; 
 unsigned int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  unix_stream_read_generic (struct unix_stream_read_state*,int) ; 
 int /*<<< orphan*/  unix_stream_splice_actor ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t unix_stream_splice_read(struct socket *sock,  loff_t *ppos,
				       struct pipe_inode_info *pipe,
				       size_t size, unsigned int flags)
{
	struct unix_stream_read_state state = {
		.recv_actor = unix_stream_splice_actor,
		.socket = sock,
		.pipe = pipe,
		.size = size,
		.splice_flags = flags,
	};

	if (unlikely(*ppos))
		return -ESPIPE;

	if (sock->file->f_flags & O_NONBLOCK ||
	    flags & SPLICE_F_NONBLOCK)
		state.flags = MSG_DONTWAIT;

	return unix_stream_read_generic(&state, false);
}