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
struct link_socket {int /*<<< orphan*/  stream_buf_data; int /*<<< orphan*/  stream_buf; void* ctrl_sd; int /*<<< orphan*/  writes; int /*<<< orphan*/  reads; void* sd; int /*<<< orphan*/  listen_handle; int /*<<< orphan*/  gremlin; } ;

/* Variables and functions */
 int D_LOW ; 
 int GREMLIN_CONNECTION_FLOOD_LEVEL (int /*<<< orphan*/ ) ; 
 int M_ERRNO ; 
 int M_WARN ; 
 void* SOCKET_UNDEFINED ; 
 int /*<<< orphan*/  close_net_event_win32 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct link_socket*) ; 
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int,char*) ; 
 scalar_t__ openvpn_close_socket (void*) ; 
 int /*<<< orphan*/  overlapped_io_close (int /*<<< orphan*/ *) ; 
 scalar_t__ socket_defined (void*) ; 
 int /*<<< orphan*/  stream_buf_close (int /*<<< orphan*/ *) ; 

void
link_socket_close(struct link_socket *sock)
{
    if (sock)
    {
#ifdef ENABLE_DEBUG
        const int gremlin = GREMLIN_CONNECTION_FLOOD_LEVEL(sock->gremlin);
#else
        const int gremlin = 0;
#endif

        if (socket_defined(sock->sd))
        {
#ifdef _WIN32
            close_net_event_win32(&sock->listen_handle, sock->sd, 0);
#endif
            if (!gremlin)
            {
                msg(D_LOW, "TCP/UDP: Closing socket");
                if (openvpn_close_socket(sock->sd))
                {
                    msg(M_WARN | M_ERRNO, "TCP/UDP: Close Socket failed");
                }
            }
            sock->sd = SOCKET_UNDEFINED;
#ifdef _WIN32
            if (!gremlin)
            {
                overlapped_io_close(&sock->reads);
                overlapped_io_close(&sock->writes);
            }
#endif
        }

        if (socket_defined(sock->ctrl_sd))
        {
            if (openvpn_close_socket(sock->ctrl_sd))
            {
                msg(M_WARN | M_ERRNO, "TCP/UDP: Close Socket (ctrl_sd) failed");
            }
            sock->ctrl_sd = SOCKET_UNDEFINED;
        }

        stream_buf_close(&sock->stream_buf);
        free_buf(&sock->stream_buf_data);
        if (!gremlin)
        {
            free(sock);
        }
    }
}