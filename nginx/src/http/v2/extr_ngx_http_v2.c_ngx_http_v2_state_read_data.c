#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {int skip_data; int in_closed; TYPE_7__* preread; TYPE_6__* request; } ;
typedef  TYPE_3__ ngx_http_v2_stream_t ;
struct TYPE_22__ {int /*<<< orphan*/  preread_size; } ;
typedef  TYPE_4__ ngx_http_v2_srv_conf_t ;
struct TYPE_20__ {size_t length; int flags; scalar_t__ padding; TYPE_3__* stream; } ;
struct TYPE_23__ {size_t payload_bytes; TYPE_2__ state; TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_24__ {int /*<<< orphan*/  pool; scalar_t__ request_body; int /*<<< orphan*/  request_body_no_buffering; scalar_t__ reading_body; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_25__ {scalar_t__ last; scalar_t__ end; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_V2_END_STREAM_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_cpymem (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 TYPE_7__* ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_6__*,scalar_t__) ; 
 TYPE_4__* ngx_http_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_connection_error (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 scalar_t__ ngx_http_v2_process_request_body (TYPE_6__*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_complete (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_save (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_skip_padded (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_read_data(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    size_t                   size;
    ngx_buf_t               *buf;
    ngx_int_t                rc;
    ngx_http_request_t      *r;
    ngx_http_v2_stream_t    *stream;
    ngx_http_v2_srv_conf_t  *h2scf;

    stream = h2c->state.stream;

    if (stream == NULL) {
        return ngx_http_v2_state_skip_padded(h2c, pos, end);
    }

    if (stream->skip_data) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                       "skipping http2 DATA frame");

        return ngx_http_v2_state_skip_padded(h2c, pos, end);
    }

    r = stream->request;

    if (r->reading_body && !r->request_body_no_buffering) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                       "skipping http2 DATA frame");

        return ngx_http_v2_state_skip_padded(h2c, pos, end);
    }

    size = end - pos;

    if (size >= h2c->state.length) {
        size = h2c->state.length;
        stream->in_closed = h2c->state.flags & NGX_HTTP_V2_END_STREAM_FLAG;
    }

    h2c->payload_bytes += size;

    if (r->request_body) {
        rc = ngx_http_v2_process_request_body(r, pos, size, stream->in_closed);

        if (rc != NGX_OK) {
            stream->skip_data = 1;
            ngx_http_finalize_request(r, rc);
        }

    } else if (size) {
        buf = stream->preread;

        if (buf == NULL) {
            h2scf = ngx_http_get_module_srv_conf(r, ngx_http_v2_module);

            buf = ngx_create_temp_buf(r->pool, h2scf->preread_size);
            if (buf == NULL) {
                return ngx_http_v2_connection_error(h2c,
                                                    NGX_HTTP_V2_INTERNAL_ERROR);
            }

            stream->preread = buf;
        }

        if (size > (size_t) (buf->end - buf->last)) {
            ngx_log_error(NGX_LOG_ALERT, h2c->connection->log, 0,
                          "http2 preread buffer overflow");
            return ngx_http_v2_connection_error(h2c,
                                                NGX_HTTP_V2_INTERNAL_ERROR);
        }

        buf->last = ngx_cpymem(buf->last, pos, size);
    }

    pos += size;
    h2c->state.length -= size;

    if (h2c->state.length) {
        return ngx_http_v2_state_save(h2c, pos, end,
                                      ngx_http_v2_state_read_data);
    }

    if (h2c->state.padding) {
        return ngx_http_v2_state_skip_padded(h2c, pos, end);
    }

    return ngx_http_v2_state_complete(h2c, pos, end);
}