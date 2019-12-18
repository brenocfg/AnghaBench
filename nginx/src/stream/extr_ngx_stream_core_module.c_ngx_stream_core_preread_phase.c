#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_21__ {int /*<<< orphan*/  phase_handler; TYPE_4__* connection; } ;
typedef  TYPE_1__ ngx_stream_session_t ;
struct TYPE_22__ {scalar_t__ (* handler ) (TYPE_1__*) ;int /*<<< orphan*/  next; } ;
typedef  TYPE_2__ ngx_stream_phase_handler_t ;
struct TYPE_23__ {int /*<<< orphan*/  preread_timeout; int /*<<< orphan*/  preread_buffer_size; } ;
typedef  TYPE_3__ ngx_stream_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {scalar_t__ (* recv ) (TYPE_4__*,size_t,size_t) ;TYPE_14__* read; TYPE_16__* buffer; TYPE_13__* log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_20__ {size_t end; size_t last; } ;
struct TYPE_19__ {scalar_t__ timer_set; int /*<<< orphan*/  handler; int /*<<< orphan*/  ready; scalar_t__ eof; scalar_t__ timedout; } ;
struct TYPE_18__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_STREAM_BAD_REQUEST ; 
 scalar_t__ NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_STREAM_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_14__*,int /*<<< orphan*/ ) ; 
 TYPE_16__* ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_14__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 int /*<<< orphan*/  ngx_stream_finalize_session (TYPE_1__*,scalar_t__) ; 
 TYPE_3__* ngx_stream_get_module_srv_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_session_handler ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_4__*,size_t,size_t) ; 
 scalar_t__ stub3 (TYPE_1__*) ; 

ngx_int_t
ngx_stream_core_preread_phase(ngx_stream_session_t *s,
    ngx_stream_phase_handler_t *ph)
{
    size_t                       size;
    ssize_t                      n;
    ngx_int_t                    rc;
    ngx_connection_t            *c;
    ngx_stream_core_srv_conf_t  *cscf;

    c = s->connection;

    c->log->action = "prereading client data";

    cscf = ngx_stream_get_module_srv_conf(s, ngx_stream_core_module);

    if (c->read->timedout) {
        rc = NGX_STREAM_OK;

    } else if (c->read->timer_set) {
        rc = NGX_AGAIN;

    } else {
        rc = ph->handler(s);
    }

    while (rc == NGX_AGAIN) {

        if (c->buffer == NULL) {
            c->buffer = ngx_create_temp_buf(c->pool, cscf->preread_buffer_size);
            if (c->buffer == NULL) {
                rc = NGX_ERROR;
                break;
            }
        }

        size = c->buffer->end - c->buffer->last;

        if (size == 0) {
            ngx_log_error(NGX_LOG_ERR, c->log, 0, "preread buffer full");
            rc = NGX_STREAM_BAD_REQUEST;
            break;
        }

        if (c->read->eof) {
            rc = NGX_STREAM_OK;
            break;
        }

        if (!c->read->ready) {
            break;
        }

        n = c->recv(c, c->buffer->last, size);

        if (n == NGX_ERROR || n == 0) {
            rc = NGX_STREAM_OK;
            break;
        }

        if (n == NGX_AGAIN) {
            break;
        }

        c->buffer->last += n;

        rc = ph->handler(s);
    }

    if (rc == NGX_AGAIN) {
        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
            return NGX_OK;
        }

        if (!c->read->timer_set) {
            ngx_add_timer(c->read, cscf->preread_timeout);
        }

        c->read->handler = ngx_stream_session_handler;

        return NGX_OK;
    }

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

    if (rc == NGX_OK) {
        s->phase_handler = ph->next;
        return NGX_AGAIN;
    }

    if (rc == NGX_DECLINED) {
        s->phase_handler++;
        return NGX_AGAIN;
    }

    if (rc == NGX_DONE) {
        return NGX_OK;
    }

    if (rc == NGX_ERROR) {
        rc = NGX_STREAM_INTERNAL_SERVER_ERROR;
    }

    ngx_stream_finalize_session(s, rc);

    return NGX_OK;
}