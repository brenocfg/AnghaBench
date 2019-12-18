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
struct TYPE_2__ {int /*<<< orphan*/  fraghdr; } ;
struct sock_xprt {int /*<<< orphan*/  sock; TYPE_1__ recv; } ;
struct msghdr {int dummy; } ;
struct kvec {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  xs_read_kvec (int /*<<< orphan*/ ,struct msghdr*,int,struct kvec*,size_t,size_t) ; 

__attribute__((used)) static ssize_t
xs_read_stream_header(struct sock_xprt *transport, struct msghdr *msg,
		int flags, size_t want, size_t seek)
{
	struct kvec kvec = {
		.iov_base = &transport->recv.fraghdr,
		.iov_len = want,
	};
	return xs_read_kvec(transport->sock, msg, flags, &kvec, want, seek);
}