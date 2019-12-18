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
struct TYPE_2__ {int sndbuf; int rcvbuf; } ;
struct link_socket {TYPE_1__ socket_buffer_sizes; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 scalar_t__ socket_defined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_buffers (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
link_socket_update_buffer_sizes(struct link_socket *ls, int rcvbuf, int sndbuf)
{
    if (ls && socket_defined(ls->sd))
    {
        ls->socket_buffer_sizes.sndbuf = sndbuf;
        ls->socket_buffer_sizes.rcvbuf = rcvbuf;
        socket_set_buffers(ls->sd, &ls->socket_buffer_sizes);
    }
}