#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {TYPE_11__* request; scalar_t__ frames; int /*<<< orphan*/ * pool; TYPE_4__* node; int /*<<< orphan*/  in_closed; int /*<<< orphan*/  out_closed; int /*<<< orphan*/  rst_sent; int /*<<< orphan*/  queued; TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_http_v2_stream_t ;
struct TYPE_18__ {int id; int /*<<< orphan*/  reuse; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_4__ ngx_http_v2_node_t ;
struct TYPE_15__ {scalar_t__ keep_pool; int /*<<< orphan*/ * pool; TYPE_3__* stream; } ;
struct TYPE_19__ {TYPE_2__* connection; scalar_t__ blocked; scalar_t__ pushing; scalar_t__ processing; TYPE_7__* free_fake_connections; TYPE_1__ state; int /*<<< orphan*/  frames; int /*<<< orphan*/  closed_nodes; int /*<<< orphan*/  closed; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_20__ {int /*<<< orphan*/  handler; scalar_t__ posted; scalar_t__ timer_set; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_21__ {struct TYPE_21__* data; TYPE_6__* write; TYPE_6__* read; scalar_t__ timedout; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_16__ {int error; TYPE_6__* read; int /*<<< orphan*/  log; } ;
struct TYPE_14__ {TYPE_7__* connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_NO_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_delete_posted_event (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_empty_handler ; 
 int /*<<< orphan*/  ngx_http_free_request (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_close_stream_handler ; 
 int /*<<< orphan*/  ngx_http_v2_handle_connection_handler ; 
 scalar_t__ ngx_http_v2_send_rst_stream (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_queue_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ngx_http_v2_close_stream(ngx_http_v2_stream_t *stream, ngx_int_t rc)
{
    ngx_pool_t                *pool;
    ngx_uint_t                 push;
    ngx_event_t               *ev;
    ngx_connection_t          *fc;
    ngx_http_v2_node_t        *node;
    ngx_http_v2_connection_t  *h2c;

    h2c = stream->connection;
    node = stream->node;

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 close stream %ui, queued %ui, "
                   "processing %ui, pushing %ui",
                   node->id, stream->queued, h2c->processing, h2c->pushing);

    fc = stream->request->connection;

    if (stream->queued) {
        fc->write->handler = ngx_http_v2_close_stream_handler;
        fc->read->handler = ngx_http_empty_handler;
        return;
    }

    if (!stream->rst_sent && !h2c->connection->error) {

        if (!stream->out_closed) {
            if (ngx_http_v2_send_rst_stream(h2c, node->id,
                                      fc->timedout ? NGX_HTTP_V2_PROTOCOL_ERROR
                                                   : NGX_HTTP_V2_INTERNAL_ERROR)
                != NGX_OK)
            {
                h2c->connection->error = 1;
            }

        } else if (!stream->in_closed) {
            if (ngx_http_v2_send_rst_stream(h2c, node->id, NGX_HTTP_V2_NO_ERROR)
                != NGX_OK)
            {
                h2c->connection->error = 1;
            }
        }
    }

    if (h2c->state.stream == stream) {
        h2c->state.stream = NULL;
    }

    push = stream->node->id % 2 == 0;

    node->stream = NULL;

    ngx_queue_insert_tail(&h2c->closed, &node->reuse);
    h2c->closed_nodes++;

    /*
     * This pool keeps decoded request headers which can be used by log phase
     * handlers in ngx_http_free_request().
     *
     * The pointer is stored into local variable because the stream object
     * will be destroyed after a call to ngx_http_free_request().
     */
    pool = stream->pool;

    h2c->frames -= stream->frames;

    ngx_http_free_request(stream->request, rc);

    if (pool != h2c->state.pool) {
        ngx_destroy_pool(pool);

    } else {
        /* pool will be destroyed when the complete header is parsed */
        h2c->state.keep_pool = 0;
    }

    ev = fc->read;

    if (ev->timer_set) {
        ngx_del_timer(ev);
    }

    if (ev->posted) {
        ngx_delete_posted_event(ev);
    }

    ev = fc->write;

    if (ev->timer_set) {
        ngx_del_timer(ev);
    }

    if (ev->posted) {
        ngx_delete_posted_event(ev);
    }

    fc->data = h2c->free_fake_connections;
    h2c->free_fake_connections = fc;

    if (push) {
        h2c->pushing--;

    } else {
        h2c->processing--;
    }

    if (h2c->processing || h2c->pushing || h2c->blocked) {
        return;
    }

    ev = h2c->connection->read;

    ev->handler = ngx_http_v2_handle_connection_handler;
    ngx_post_event(ev, &ngx_posted_events);
}