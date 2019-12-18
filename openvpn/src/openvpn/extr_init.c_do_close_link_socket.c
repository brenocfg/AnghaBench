#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * bind_local; int /*<<< orphan*/  actual; TYPE_2__* current_remote; } ;
struct TYPE_11__ {TYPE_6__ link_socket_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  resolve_in_advance; scalar_t__ persist_local_ip; scalar_t__ persist_remote_ip; scalar_t__ no_advance; } ;
struct TYPE_7__ {int /*<<< orphan*/ * link_socket; scalar_t__ link_socket_owned; } ;
struct context {TYPE_5__ c1; TYPE_4__ options; TYPE_3__* sig; TYPE_1__ c2; } ;
struct TYPE_9__ {scalar_t__ signal_received; scalar_t__ source; } ;
struct TYPE_8__ {scalar_t__ ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGUSR1 ; 
 scalar_t__ SIG_SOURCE_HARD ; 
 int /*<<< orphan*/  clear_remote_addrlist (TYPE_6__*,int) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_socket_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_close_link_socket(struct context *c)
{
    if (c->c2.link_socket && c->c2.link_socket_owned)
    {
        link_socket_close(c->c2.link_socket);
        c->c2.link_socket = NULL;
    }


    /* Preserve the resolved list of remote if the user request to or if we want
     * reconnect to the same host again or there are still addresses that need
     * to be tried */
    if (!(c->sig->signal_received == SIGUSR1
          && ( (c->options.persist_remote_ip)
               ||
               ( c->sig->source != SIG_SOURCE_HARD
                 && ((c->c1.link_socket_addr.current_remote && c->c1.link_socket_addr.current_remote->ai_next)
                     || c->options.no_advance))
               )))
    {
        clear_remote_addrlist(&c->c1.link_socket_addr, !c->options.resolve_in_advance);
    }

    /* Clear the remote actual address when persist_remote_ip is not in use */
    if (!(c->sig->signal_received == SIGUSR1 && c->options.persist_remote_ip))
    {
        CLEAR(c->c1.link_socket_addr.actual);
    }

    if (!(c->sig->signal_received == SIGUSR1 && c->options.persist_local_ip))
    {
        if (c->c1.link_socket_addr.bind_local && !c->options.resolve_in_advance)
        {
            freeaddrinfo(c->c1.link_socket_addr.bind_local);
        }

        c->c1.link_socket_addr.bind_local = NULL;
    }
}