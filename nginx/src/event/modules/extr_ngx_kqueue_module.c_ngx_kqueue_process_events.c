#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
typedef  int ngx_msec_t ;
typedef  int ngx_int_t ;
struct TYPE_14__ {int instance; int pending_eof; int ready; int kq_vnode; int complete; int /*<<< orphan*/  (* handler ) (TYPE_1__*) ;scalar_t__ accept; int /*<<< orphan*/  kq_errno; int /*<<< orphan*/  available; int /*<<< orphan*/  active; int /*<<< orphan*/  oneshot; TYPE_5__* log; int /*<<< orphan*/  closed; } ;
typedef  TYPE_1__ ngx_event_t ;
typedef  int ngx_err_t ;
struct TYPE_15__ {TYPE_5__* log; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_16__ {int log_level; } ;
struct TYPE_13__ {int flags; int filter; int /*<<< orphan*/  fflags; int /*<<< orphan*/  data; scalar_t__ udata; scalar_t__ ident; } ;

/* Variables and functions */
#define  EVFILT_AIO 132 
#define  EVFILT_READ 131 
 int EVFILT_TIMER ; 
#define  EVFILT_USER 130 
#define  EVFILT_VNODE 129 
#define  EVFILT_WRITE 128 
 int EV_EOF ; 
 int EV_ERROR ; 
 int NGX_EINTR ; 
 int NGX_ERROR ; 
 int NGX_LOG_ALERT ; 
 int NGX_LOG_DEBUG_CONNECTION ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int NGX_LOG_INFO ; 
 int NGX_OK ; 
 int NGX_POST_EVENTS ; 
 int NGX_TIMER_INFINITE ; 
 int NGX_UPDATE_TIME ; 
 int /*<<< orphan*/  change_list ; 
 TYPE_10__* event_list ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_10__*,int,struct timespec*) ; 
 scalar_t__ nchanges ; 
 scalar_t__ nevents ; 
 int ngx_errno ; 
 scalar_t__ ngx_event_timer_alarm ; 
 int /*<<< orphan*/  ngx_kqueue ; 
 int /*<<< orphan*/  ngx_kqueue_dump_event (TYPE_5__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int,TYPE_5__*,int,char*,...) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_accept_events ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_kqueue_process_events(ngx_cycle_t *cycle, ngx_msec_t timer,
    ngx_uint_t flags)
{
    int               events, n;
    ngx_int_t         i, instance;
    ngx_uint_t        level;
    ngx_err_t         err;
    ngx_event_t      *ev;
    ngx_queue_t      *queue;
    struct timespec   ts, *tp;

    n = (int) nchanges;
    nchanges = 0;

    if (timer == NGX_TIMER_INFINITE) {
        tp = NULL;

    } else {

        ts.tv_sec = timer / 1000;
        ts.tv_nsec = (timer % 1000) * 1000000;

        /*
         * 64-bit Darwin kernel has the bug: kernel level ts.tv_nsec is
         * the int32_t while user level ts.tv_nsec is the long (64-bit),
         * so on the big endian PowerPC all nanoseconds are lost.
         */

#if (NGX_DARWIN_KEVENT_BUG)
        ts.tv_nsec <<= 32;
#endif

        tp = &ts;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "kevent timer: %M, changes: %d", timer, n);

    events = kevent(ngx_kqueue, change_list, n, event_list, (int) nevents, tp);

    err = (events == -1) ? ngx_errno : 0;

    if (flags & NGX_UPDATE_TIME || ngx_event_timer_alarm) {
        ngx_time_update();
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "kevent events: %d", events);

    if (err) {
        if (err == NGX_EINTR) {

            if (ngx_event_timer_alarm) {
                ngx_event_timer_alarm = 0;
                return NGX_OK;
            }

            level = NGX_LOG_INFO;

        } else {
            level = NGX_LOG_ALERT;
        }

        ngx_log_error(level, cycle->log, err, "kevent() failed");
        return NGX_ERROR;
    }

    if (events == 0) {
        if (timer != NGX_TIMER_INFINITE) {
            return NGX_OK;
        }

        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                      "kevent() returned no events without timeout");
        return NGX_ERROR;
    }

    for (i = 0; i < events; i++) {

        ngx_kqueue_dump_event(cycle->log, &event_list[i]);

        if (event_list[i].flags & EV_ERROR) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, event_list[i].data,
                          "kevent() error on %d filter:%d flags:%04Xd",
                          (int) event_list[i].ident, event_list[i].filter,
                          event_list[i].flags);
            continue;
        }

#if (NGX_HAVE_TIMER_EVENT)

        if (event_list[i].filter == EVFILT_TIMER) {
            ngx_time_update();
            continue;
        }

#endif

        ev = (ngx_event_t *) event_list[i].udata;

        switch (event_list[i].filter) {

        case EVFILT_READ:
        case EVFILT_WRITE:

            instance = (uintptr_t) ev & 1;
            ev = (ngx_event_t *) ((uintptr_t) ev & (uintptr_t) ~1);

            if (ev->closed || ev->instance != instance) {

                /*
                 * the stale event from a file descriptor
                 * that was just closed in this iteration
                 */

                ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                               "kevent: stale event %p", ev);
                continue;
            }

            if (ev->log && (ev->log->log_level & NGX_LOG_DEBUG_CONNECTION)) {
                ngx_kqueue_dump_event(ev->log, &event_list[i]);
            }

            if (ev->oneshot) {
                ev->active = 0;
            }

            ev->available = event_list[i].data;

            if (event_list[i].flags & EV_EOF) {
                ev->pending_eof = 1;
                ev->kq_errno = event_list[i].fflags;
            }

            ev->ready = 1;

            break;

        case EVFILT_VNODE:
            ev->kq_vnode = 1;

            break;

        case EVFILT_AIO:
            ev->complete = 1;
            ev->ready = 1;

            break;

#ifdef EVFILT_USER
        case EVFILT_USER:
            break;
#endif

        default:
            ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                          "unexpected kevent() filter %d",
                          event_list[i].filter);
            continue;
        }

        if (flags & NGX_POST_EVENTS) {
            queue = ev->accept ? &ngx_posted_accept_events
                               : &ngx_posted_events;

            ngx_post_event(ev, queue);

            continue;
        }

        ev->handler(ev);
    }

    return NGX_OK;
}