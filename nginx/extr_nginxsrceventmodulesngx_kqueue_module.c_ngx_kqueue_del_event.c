#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int disabled; size_t index; int /*<<< orphan*/  data; int /*<<< orphan*/  log; scalar_t__ active; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {scalar_t__ udata; } ;

/* Variables and functions */
 int EV_DELETE ; 
 int NGX_CLOSE_EVENT ; 
 int NGX_DISABLE_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_4__* change_list ; 
 size_t nchanges ; 
 int /*<<< orphan*/  ngx_event_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_kqueue_set_event (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_kqueue_del_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_int_t     rc;
    ngx_event_t  *e;

    ev->active = 0;
    ev->disabled = 0;

    if (ev->index < nchanges
        && ((uintptr_t) change_list[ev->index].udata & (uintptr_t) ~1)
            == (uintptr_t) ev)
    {
        ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                       "kevent deleted: %d: ft:%i",
                       ngx_event_ident(ev->data), event);

        /* if the event is still not passed to a kernel we will not pass it */

        nchanges--;

        if (ev->index < nchanges) {
            e = (ngx_event_t *)
                    ((uintptr_t) change_list[nchanges].udata & (uintptr_t) ~1);
            change_list[ev->index] = change_list[nchanges];
            e->index = ev->index;
        }

        return NGX_OK;
    }

    /*
     * when the file descriptor is closed the kqueue automatically deletes
     * its filters so we do not need to delete explicitly the event
     * before the closing the file descriptor.
     */

    if (flags & NGX_CLOSE_EVENT) {
        return NGX_OK;
    }

    if (flags & NGX_DISABLE_EVENT) {
        ev->disabled = 1;

    } else {
        flags |= EV_DELETE;
    }

    rc = ngx_kqueue_set_event(ev, event, flags);

    return rc;
}