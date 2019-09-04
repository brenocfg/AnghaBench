#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_4__ {int oneshot; uintptr_t instance; int active; int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; TYPE_1__* read; TYPE_1__* write; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_READ_EVENT ; 
 scalar_t__ POLLIN ; 
 scalar_t__ POLLOUT ; 
 int /*<<< orphan*/  PORT_SOURCE_FD ; 
 int /*<<< orphan*/  ep ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int port_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 

__attribute__((used)) static ngx_int_t
ngx_eventport_add_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_int_t          events, prev;
    ngx_event_t       *e;
    ngx_connection_t  *c;

    c = ev->data;

    events = event;

    if (event == NGX_READ_EVENT) {
        e = c->write;
        prev = POLLOUT;
#if (NGX_READ_EVENT != POLLIN)
        events = POLLIN;
#endif

    } else {
        e = c->read;
        prev = POLLIN;
#if (NGX_WRITE_EVENT != POLLOUT)
        events = POLLOUT;
#endif
    }

    if (e->oneshot) {
        events |= prev;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "eventport add event: fd:%d ev:%04Xi", c->fd, events);

    if (port_associate(ep, PORT_SOURCE_FD, c->fd, events,
                       (void *) ((uintptr_t) ev | ev->instance))
        == -1)
    {
        ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_errno,
                      "port_associate() failed");
        return NGX_ERROR;
    }

    ev->active = 1;
    ev->oneshot = 1;

    return NGX_OK;
}