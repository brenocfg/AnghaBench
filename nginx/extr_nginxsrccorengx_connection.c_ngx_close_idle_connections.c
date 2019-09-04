#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_5__ {size_t connection_n; TYPE_2__* connections; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_6__ {scalar_t__ fd; int close; TYPE_3__* read; scalar_t__ idle; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
ngx_close_idle_connections(ngx_cycle_t *cycle)
{
    ngx_uint_t         i;
    ngx_connection_t  *c;

    c = cycle->connections;

    for (i = 0; i < cycle->connection_n; i++) {

        /* THREAD: lock */

        if (c[i].fd != (ngx_socket_t) -1 && c[i].idle) {
            c[i].close = 1;
            c[i].read->handler(c[i].read);
        }
    }
}