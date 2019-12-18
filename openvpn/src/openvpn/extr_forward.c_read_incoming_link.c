#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  link_socket; int /*<<< orphan*/  explicit_exit_notification_interval; int /*<<< orphan*/  from; int /*<<< orphan*/  buf; int /*<<< orphan*/  frame; TYPE_1__* buffers; } ;
struct TYPE_5__ {scalar_t__ inetd; } ;
struct context {TYPE_3__ c2; TYPE_2__ options; } ;
struct buffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_link_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_STREAM_ERRORS ; 
 int /*<<< orphan*/  FRAME_HEADROOM_ADJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRAME_HEADROOM_MARKER_READ_LINK ; 
 int /*<<< orphan*/  PERF_READ_IN_LINK ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_status (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ event_timeout_defined (int /*<<< orphan*/ *) ; 
 int link_socket_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  management_sleep (int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 scalar_t__ port_share ; 
 int /*<<< orphan*/  port_share_redirect (scalar_t__,struct buffer const*,int const) ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ socket_connection_reset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket_foreign_protocol_detected (int /*<<< orphan*/ ) ; 
 struct buffer* socket_foreign_protocol_head (int /*<<< orphan*/ ) ; 
 int socket_foreign_protocol_sd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socks_postprocess_incoming_link (struct context*) ; 

void
read_incoming_link(struct context *c)
{
    /*
     * Set up for recvfrom call to read datagram
     * sent to our TCP/UDP port.
     */
    int status;

    /*ASSERT (!c->c2.to_tun.len);*/

    perf_push(PERF_READ_IN_LINK);

    c->c2.buf = c->c2.buffers->read_link_buf;
    ASSERT(buf_init(&c->c2.buf, FRAME_HEADROOM_ADJ(&c->c2.frame, FRAME_HEADROOM_MARKER_READ_LINK)));

    status = link_socket_read(c->c2.link_socket,
                              &c->c2.buf,
                              &c->c2.from);

    if (socket_connection_reset(c->c2.link_socket, status))
    {
#if PORT_SHARE
        if (port_share && socket_foreign_protocol_detected(c->c2.link_socket))
        {
            const struct buffer *fbuf = socket_foreign_protocol_head(c->c2.link_socket);
            const int sd = socket_foreign_protocol_sd(c->c2.link_socket);
            port_share_redirect(port_share, fbuf, sd);
            register_signal(c, SIGTERM, "port-share-redirect");
        }
        else
#endif
        {
            /* received a disconnect from a connection-oriented protocol */
            if (c->options.inetd)
            {
                register_signal(c, SIGTERM, "connection-reset-inetd");
                msg(D_STREAM_ERRORS, "Connection reset, inetd/xinetd exit [%d]", status);
            }
            else
            {
#ifdef ENABLE_OCC
                if (event_timeout_defined(&c->c2.explicit_exit_notification_interval))
                {
                    msg(D_STREAM_ERRORS, "Connection reset during exit notification period, ignoring [%d]", status);
                    management_sleep(1);
                }
                else
#endif
                {
                    register_signal(c, SIGUSR1, "connection-reset"); /* SOFT-SIGUSR1 -- TCP connection reset */
                    msg(D_STREAM_ERRORS, "Connection reset, restarting [%d]", status);
                }
            }
        }
        perf_pop();
        return;
    }

    /* check recvfrom status */
    check_status(status, "read", c->c2.link_socket, NULL);

    /* Remove socks header if applicable */
    socks_postprocess_incoming_link(c);

    perf_pop();
}