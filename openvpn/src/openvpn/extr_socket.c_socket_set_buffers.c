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
struct socket_buffer_size {scalar_t__ rcvbuf; scalar_t__ sndbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_OSBUF ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int const,int,int const,int) ; 
 int socket_get_rcvbuf (int) ; 
 int socket_get_sndbuf (int) ; 
 int /*<<< orphan*/  socket_set_rcvbuf (int,scalar_t__) ; 
 int /*<<< orphan*/  socket_set_sndbuf (int,scalar_t__) ; 

__attribute__((used)) static void
socket_set_buffers(int fd, const struct socket_buffer_size *sbs)
{
    if (sbs)
    {
        const int sndbuf_old = socket_get_sndbuf(fd);
        const int rcvbuf_old = socket_get_rcvbuf(fd);

        if (sbs->sndbuf)
        {
            socket_set_sndbuf(fd, sbs->sndbuf);
        }

        if (sbs->rcvbuf)
        {
            socket_set_rcvbuf(fd, sbs->rcvbuf);
        }

        msg(D_OSBUF, "Socket Buffers: R=[%d->%d] S=[%d->%d]",
            rcvbuf_old,
            socket_get_rcvbuf(fd),
            sndbuf_old,
            socket_get_sndbuf(fd));
    }
}