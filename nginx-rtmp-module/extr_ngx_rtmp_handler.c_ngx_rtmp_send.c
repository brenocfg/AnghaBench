#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t out_pos; size_t out_last; scalar_t__ out_bpos; int ping_reset; size_t out_queue; int /*<<< orphan*/  posted_dry_events; TYPE_8__* out_chain; TYPE_8__** out; int /*<<< orphan*/  out_bytes; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {scalar_t__ active; scalar_t__ timer_set; scalar_t__ timedout; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_15__ {int timedout; scalar_t__ (* send ) (TYPE_4__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  write; int /*<<< orphan*/  log; scalar_t__ destroyed; TYPE_2__* data; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_16__ {TYPE_1__* buf; struct TYPE_16__* next; } ;
struct TYPE_12__ {scalar_t__ pos; scalar_t__ last; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_WRITE_EVENT ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_cycle ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_event_process_posted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_handle_write_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_bw_out ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_free_shared_chain (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_update_bandwidth (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ngx_rtmp_send(ngx_event_t *wev)
{
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;
    ngx_int_t                   n;
    ngx_rtmp_core_srv_conf_t   *cscf;

    c = wev->data;
    s = c->data;

    if (c->destroyed) {
        return;
    }

    if (wev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                "client timed out");
        c->timedout = 1;
        ngx_rtmp_finalize_session(s);
        return;
    }

    if (wev->timer_set) {
        ngx_del_timer(wev);
    }

    if (s->out_chain == NULL && s->out_pos != s->out_last) {
        s->out_chain = s->out[s->out_pos];
        s->out_bpos = s->out_chain->buf->pos;
    }

    while (s->out_chain) {
        n = c->send(c, s->out_bpos, s->out_chain->buf->last - s->out_bpos);

        if (n == NGX_AGAIN || n == 0) {
            ngx_add_timer(c->write, s->timeout);
            if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
                ngx_rtmp_finalize_session(s);
            }
            return;
        }

        if (n < 0) {
            ngx_rtmp_finalize_session(s);
            return;
        }

        s->out_bytes += n;
        s->ping_reset = 1;
        ngx_rtmp_update_bandwidth(&ngx_rtmp_bw_out, n);
        s->out_bpos += n;
        if (s->out_bpos == s->out_chain->buf->last) {
            s->out_chain = s->out_chain->next;
            if (s->out_chain == NULL) {
                cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);
                ngx_rtmp_free_shared_chain(cscf, s->out[s->out_pos]);
                ++s->out_pos;
                s->out_pos %= s->out_queue;
                if (s->out_pos == s->out_last) {
                    break;
                }
                s->out_chain = s->out[s->out_pos];
            }
            s->out_bpos = s->out_chain->buf->pos;
        }
    }

    if (wev->active) {
        ngx_del_event(wev, NGX_WRITE_EVENT, 0);
    }

    ngx_event_process_posted((ngx_cycle_t *) ngx_cycle, &s->posted_dry_events);
}