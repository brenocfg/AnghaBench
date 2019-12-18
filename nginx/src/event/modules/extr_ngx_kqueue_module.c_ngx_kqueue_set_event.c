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
typedef  scalar_t__ u_short ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct kevent {short filter; int fflags; scalar_t__ data; int /*<<< orphan*/  udata; scalar_t__ flags; int /*<<< orphan*/  ident; } ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_4__ {uintptr_t instance; size_t index; int /*<<< orphan*/  log; scalar_t__ available; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ EVFILT_VNODE ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_FLUSH_EVENT ; 
 int /*<<< orphan*/  NGX_KQUEUE_UDATA_T (uintptr_t) ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int NGX_LOWAT_EVENT ; 
 scalar_t__ NGX_OK ; 
 int NOTE_ATTRIB ; 
 int NOTE_DELETE ; 
 int NOTE_EXTEND ; 
 int NOTE_LOWAT ; 
 int NOTE_RENAME ; 
 int NOTE_REVOKE ; 
 int NOTE_WRITE ; 
 struct kevent* change_list ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 size_t max_changes ; 
 size_t nchanges ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_kqueue ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_kqueue_set_event(ngx_event_t *ev, ngx_int_t filter, ngx_uint_t flags)
{
    struct kevent     *kev;
    struct timespec    ts;
    ngx_connection_t  *c;

    c = ev->data;

    ngx_log_debug3(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "kevent set event: %d: ft:%i fl:%04Xi",
                   c->fd, filter, flags);

    if (nchanges >= max_changes) {
        ngx_log_error(NGX_LOG_WARN, ev->log, 0,
                      "kqueue change list is filled up");

        ts.tv_sec = 0;
        ts.tv_nsec = 0;

        if (kevent(ngx_kqueue, change_list, (int) nchanges, NULL, 0, &ts)
            == -1)
        {
            ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_errno, "kevent() failed");
            return NGX_ERROR;
        }

        nchanges = 0;
    }

    kev = &change_list[nchanges];

    kev->ident = c->fd;
    kev->filter = (short) filter;
    kev->flags = (u_short) flags;
    kev->udata = NGX_KQUEUE_UDATA_T ((uintptr_t) ev | ev->instance);

    if (filter == EVFILT_VNODE) {
        kev->fflags = NOTE_DELETE|NOTE_WRITE|NOTE_EXTEND
                                 |NOTE_ATTRIB|NOTE_RENAME
#if (__FreeBSD__ == 4 && __FreeBSD_version >= 430000) \
    || __FreeBSD_version >= 500018
                                 |NOTE_REVOKE
#endif
                      ;
        kev->data = 0;

    } else {
#if (NGX_HAVE_LOWAT_EVENT)
        if (flags & NGX_LOWAT_EVENT) {
            kev->fflags = NOTE_LOWAT;
            kev->data = ev->available;

        } else {
            kev->fflags = 0;
            kev->data = 0;
        }
#else
        kev->fflags = 0;
        kev->data = 0;
#endif
    }

    ev->index = nchanges;
    nchanges++;

    if (flags & NGX_FLUSH_EVENT) {
        ts.tv_sec = 0;
        ts.tv_nsec = 0;

        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, ev->log, 0, "kevent flush");

        if (kevent(ngx_kqueue, change_list, (int) nchanges, NULL, 0, &ts)
            == -1)
        {
            ngx_log_error(NGX_LOG_ALERT, ev->log, ngx_errno, "kevent() failed");
            return NGX_ERROR;
        }

        nchanges = 0;
    }

    return NGX_OK;
}