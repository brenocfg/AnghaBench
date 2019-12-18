#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_stream_t ;
struct TYPE_23__ {int out_queue; int /*<<< orphan*/  buflen; int /*<<< orphan*/  timeout; int /*<<< orphan*/  epoch; int /*<<< orphan*/  posted_dry_events; int /*<<< orphan*/ * in_streams; int /*<<< orphan*/  out_cork; int /*<<< orphan*/ * ctx; TYPE_7__* connection; int /*<<< orphan*/ * addr_text; scalar_t__* srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_24__ {TYPE_3__* session; int /*<<< orphan*/ * client; } ;
typedef  TYPE_4__ ngx_rtmp_error_log_ctx_t ;
struct TYPE_25__ {int out_queue; int max_streams; int /*<<< orphan*/  buflen; int /*<<< orphan*/  timeout; int /*<<< orphan*/  out_cork; } ;
typedef  TYPE_5__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_26__ {int /*<<< orphan*/  addr_text; TYPE_1__* ctx; } ;
typedef  TYPE_6__ ngx_rtmp_addr_conf_t ;
struct TYPE_27__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log_error; TYPE_2__* log; int /*<<< orphan*/  number; int /*<<< orphan*/  addr_text; TYPE_3__* data; } ;
typedef  TYPE_7__ ngx_connection_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_22__ {int /*<<< orphan*/ * action; TYPE_4__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  connection; } ;
struct TYPE_21__ {scalar_t__* srv_conf; int /*<<< orphan*/  main_conf; } ;
struct TYPE_20__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_CONNECT ; 
 int /*<<< orphan*/  NGX_RTMP_DEFAULT_CHUNK_SIZE ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_close_connection (TYPE_7__*) ; 
 TYPE_14__ ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_3__*) ; 
 scalar_t__ ngx_rtmp_fire_event (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_rtmp_get_module_srv_conf (TYPE_3__*,TYPE_14__) ; 
 int /*<<< orphan*/  ngx_rtmp_log_error ; 
 int ngx_rtmp_max_module ; 
 int /*<<< orphan*/  ngx_rtmp_set_chunk_size (TYPE_3__*,int /*<<< orphan*/ ) ; 

ngx_rtmp_session_t *
ngx_rtmp_init_session(ngx_connection_t *c, ngx_rtmp_addr_conf_t *addr_conf)
{
    ngx_rtmp_session_t             *s;
    ngx_rtmp_core_srv_conf_t       *cscf;
    ngx_rtmp_error_log_ctx_t       *ctx;

    s = ngx_pcalloc(c->pool, sizeof(ngx_rtmp_session_t) +
            sizeof(ngx_chain_t *) * ((ngx_rtmp_core_srv_conf_t *)
                addr_conf->ctx-> srv_conf[ngx_rtmp_core_module
                    .ctx_index])->out_queue);
    if (s == NULL) {
        ngx_rtmp_close_connection(c);
        return NULL;
    }

    s->main_conf = addr_conf->ctx->main_conf;
    s->srv_conf = addr_conf->ctx->srv_conf;

    s->addr_text = &addr_conf->addr_text;

    c->data = s;
    s->connection = c;

    ctx = ngx_palloc(c->pool, sizeof(ngx_rtmp_error_log_ctx_t));
    if (ctx == NULL) {
        ngx_rtmp_close_connection(c);
        return NULL;
    }

    ctx->client = &c->addr_text;
    ctx->session = s;

    c->log->connection = c->number;
    c->log->handler = ngx_rtmp_log_error;
    c->log->data = ctx;
    c->log->action = NULL;

    c->log_error = NGX_ERROR_INFO;

    s->ctx = ngx_pcalloc(c->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (s->ctx == NULL) {
        ngx_rtmp_close_connection(c);
        return NULL;
    }

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    s->out_queue = cscf->out_queue;
    s->out_cork = cscf->out_cork;
    s->in_streams = ngx_pcalloc(c->pool, sizeof(ngx_rtmp_stream_t)
            * cscf->max_streams);
    if (s->in_streams == NULL) {
        ngx_rtmp_close_connection(c);
        return NULL;
    }

#if (nginx_version >= 1007005)
    ngx_queue_init(&s->posted_dry_events);
#endif

    s->epoch = ngx_current_msec;
    s->timeout = cscf->timeout;
    s->buflen = cscf->buflen;
    ngx_rtmp_set_chunk_size(s, NGX_RTMP_DEFAULT_CHUNK_SIZE);


    if (ngx_rtmp_fire_event(s, NGX_RTMP_CONNECT, NULL, NULL) != NGX_OK) {
        ngx_rtmp_finalize_session(s);
        return NULL;
    }

    return s;
}