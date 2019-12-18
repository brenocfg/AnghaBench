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
struct TYPE_2__ {scalar_t__ len; int copied; size_t offset; int /*<<< orphan*/  calldir; int /*<<< orphan*/  fraghdr; } ;
struct sock_xprt {TYPE_1__ recv; int /*<<< orphan*/  sock; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  member_0; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ESHUTDOWN ; 
 int MSG_TRUNC ; 
#define  RPC_CALL 129 
 int RPC_FRAGMENT_SIZE_MASK ; 
#define  RPC_REPLY 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  trace_xs_stream_read_request (struct sock_xprt*) ; 
 size_t xs_read_discard (int /*<<< orphan*/ ,struct msghdr*,int,int) ; 
 size_t xs_read_stream_call (struct sock_xprt*,struct msghdr*,int) ; 
 size_t xs_read_stream_header (struct sock_xprt*,struct msghdr*,int,size_t,size_t) ; 
 size_t xs_read_stream_headersize (int) ; 
 size_t xs_read_stream_reply (struct sock_xprt*,struct msghdr*,int) ; 
 scalar_t__ xs_read_stream_request_done (struct sock_xprt*) ; 

__attribute__((used)) static ssize_t
xs_read_stream(struct sock_xprt *transport, int flags)
{
	struct msghdr msg = { 0 };
	size_t want, read = 0;
	ssize_t ret = 0;

	if (transport->recv.len == 0) {
		want = xs_read_stream_headersize(transport->recv.copied != 0);
		ret = xs_read_stream_header(transport, &msg, flags, want,
				transport->recv.offset);
		if (ret <= 0)
			goto out_err;
		transport->recv.offset = ret;
		if (transport->recv.offset != want)
			return transport->recv.offset;
		transport->recv.len = be32_to_cpu(transport->recv.fraghdr) &
			RPC_FRAGMENT_SIZE_MASK;
		transport->recv.offset -= sizeof(transport->recv.fraghdr);
		read = ret;
	}

	switch (be32_to_cpu(transport->recv.calldir)) {
	default:
		msg.msg_flags |= MSG_TRUNC;
		break;
	case RPC_CALL:
		ret = xs_read_stream_call(transport, &msg, flags);
		break;
	case RPC_REPLY:
		ret = xs_read_stream_reply(transport, &msg, flags);
	}
	if (msg.msg_flags & MSG_TRUNC) {
		transport->recv.calldir = cpu_to_be32(-1);
		transport->recv.copied = -1;
	}
	if (ret < 0)
		goto out_err;
	read += ret;
	if (transport->recv.offset < transport->recv.len) {
		if (!(msg.msg_flags & MSG_TRUNC))
			return read;
		msg.msg_flags = 0;
		ret = xs_read_discard(transport->sock, &msg, flags,
				transport->recv.len - transport->recv.offset);
		if (ret <= 0)
			goto out_err;
		transport->recv.offset += ret;
		read += ret;
		if (transport->recv.offset != transport->recv.len)
			return read;
	}
	if (xs_read_stream_request_done(transport)) {
		trace_xs_stream_read_request(transport);
		transport->recv.copied = 0;
	}
	transport->recv.offset = 0;
	transport->recv.len = 0;
	return read;
out_err:
	return ret != 0 ? ret : -ESHUTDOWN;
}