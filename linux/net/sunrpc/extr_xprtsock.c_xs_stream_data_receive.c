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
struct sock_xprt {int /*<<< orphan*/  xprt; int /*<<< orphan*/  recv_mutex; int /*<<< orphan*/ * sock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ESHUTDOWN ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  kernel_sock_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xs_stream_read_data (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  xs_poll_check_readable (struct sock_xprt*) ; 
 size_t xs_read_stream (struct sock_xprt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xs_stream_data_receive(struct sock_xprt *transport)
{
	size_t read = 0;
	ssize_t ret = 0;

	mutex_lock(&transport->recv_mutex);
	if (transport->sock == NULL)
		goto out;
	for (;;) {
		ret = xs_read_stream(transport, MSG_DONTWAIT);
		if (ret < 0)
			break;
		read += ret;
		cond_resched();
	}
	if (ret == -ESHUTDOWN)
		kernel_sock_shutdown(transport->sock, SHUT_RDWR);
	else
		xs_poll_check_readable(transport);
out:
	mutex_unlock(&transport->recv_mutex);
	trace_xs_stream_read_data(&transport->xprt, ret, read);
}