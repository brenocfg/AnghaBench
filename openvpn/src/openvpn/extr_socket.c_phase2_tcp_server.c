#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* lsa; } ;
struct link_socket {int mode; TYPE_2__ info; int /*<<< orphan*/  sd; } ;
struct TYPE_3__ {int /*<<< orphan*/  actual; int /*<<< orphan*/  bind_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  LS_MODE_DEFAULT 130 
#define  LS_MODE_TCP_ACCEPT_FROM 129 
#define  LS_MODE_TCP_LISTEN 128 
 int SIGTERM ; 
 int /*<<< orphan*/  socket_defined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_do_accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_do_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  socket_listen_accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int,int volatile*) ; 
 int /*<<< orphan*/  tcp_connection_established (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
phase2_tcp_server(struct link_socket *sock, const char *remote_dynamic,
                  volatile int *signal_received)
{
    switch (sock->mode)
    {
        case LS_MODE_DEFAULT:
            sock->sd = socket_listen_accept(sock->sd,
                                            &sock->info.lsa->actual,
                                            remote_dynamic,
                                            sock->info.lsa->bind_local,
                                            true,
                                            false,
                                            signal_received);
            break;

        case LS_MODE_TCP_LISTEN:
            socket_do_listen(sock->sd,
                             sock->info.lsa->bind_local,
                             true,
                             false);
            break;

        case LS_MODE_TCP_ACCEPT_FROM:
            sock->sd = socket_do_accept(sock->sd,
                                        &sock->info.lsa->actual,
                                        false);
            if (!socket_defined(sock->sd))
            {
                *signal_received = SIGTERM;
                return;
            }
            tcp_connection_established(&sock->info.lsa->actual);
            break;

        default:
            ASSERT(0);
    }
}