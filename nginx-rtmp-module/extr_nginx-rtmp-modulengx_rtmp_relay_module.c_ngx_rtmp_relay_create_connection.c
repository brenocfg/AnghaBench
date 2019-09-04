#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
struct sockaddr {int dummy; } ;
struct TYPE_31__ {char* data; int len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_32__ {int relay; int /*<<< orphan*/  flashver; int /*<<< orphan*/  app_conf; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_30__ {size_t naddrs; TYPE_11__* addrs; TYPE_2__ uri; TYPE_2__ url; } ;
struct TYPE_33__ {size_t counter; TYPE_1__ url; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  live; TYPE_2__ play_path; TYPE_2__ flash_ver; TYPE_2__ swf_url; TYPE_2__ page_url; TYPE_2__ tc_url; TYPE_2__ app; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
typedef  TYPE_4__ ngx_rtmp_relay_target_t ;
struct TYPE_29__ {scalar_t__ len; } ;
struct TYPE_34__ {TYPE_3__* session; TYPE_18__ url; int /*<<< orphan*/  log; TYPE_18__ play_path; TYPE_18__ app; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  live; TYPE_18__ flash_ver; TYPE_18__ swf_url; TYPE_18__ page_url; TYPE_18__ tc_url; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; TYPE_18__ name; } ;
typedef  TYPE_5__ ngx_rtmp_relay_ctx_t ;
struct TYPE_35__ {int /*<<< orphan*/ * log; } ;
typedef  TYPE_6__ ngx_rtmp_relay_app_conf_t ;
struct TYPE_36__ {int /*<<< orphan*/  app_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_7__ ngx_rtmp_conf_ctx_t ;
struct TYPE_37__ {int /*<<< orphan*/  addr_text; TYPE_7__* ctx; } ;
typedef  TYPE_8__ ngx_rtmp_addr_conf_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_38__ {TYPE_10__* connection; int /*<<< orphan*/  socklen; struct sockaddr* sockaddr; int /*<<< orphan*/ * name; int /*<<< orphan*/  free; int /*<<< orphan*/  get; int /*<<< orphan*/ * log; } ;
typedef  TYPE_9__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_27__ {TYPE_18__ addr_text; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_10__ ngx_connection_t ;
struct TYPE_28__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; int /*<<< orphan*/  name; } ;
typedef  TYPE_11__ ngx_addr_t ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_client_handshake (TYPE_3__*,int) ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_init_session (TYPE_10__*,TYPE_8__*) ; 
 scalar_t__ ngx_rtmp_relay_copy_str (int /*<<< orphan*/ *,TYPE_18__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_free_peer ; 
 int /*<<< orphan*/  ngx_rtmp_relay_get_peer ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 
 char* ngx_strlchr (char*,char*,char) ; 

__attribute__((used)) static ngx_rtmp_relay_ctx_t *
ngx_rtmp_relay_create_connection(ngx_rtmp_conf_ctx_t *cctx, ngx_str_t* name,
        ngx_rtmp_relay_target_t *target)
{
    ngx_rtmp_relay_app_conf_t      *racf;
    ngx_rtmp_relay_ctx_t           *rctx;
    ngx_rtmp_addr_conf_t           *addr_conf;
    ngx_rtmp_conf_ctx_t            *addr_ctx;
    ngx_rtmp_session_t             *rs;
    ngx_peer_connection_t          *pc;
    ngx_connection_t               *c;
    ngx_addr_t                     *addr;
    ngx_pool_t                     *pool;
    ngx_int_t                       rc;
    ngx_str_t                       v, *uri;
    u_char                         *first, *last, *p;

    racf = ngx_rtmp_get_module_app_conf(cctx, ngx_rtmp_relay_module);

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, racf->log, 0,
                   "relay: create remote context");

    pool = NULL;
    pool = ngx_create_pool(4096, racf->log);
    if (pool == NULL) {
        return NULL;
    }

    rctx = ngx_pcalloc(pool, sizeof(ngx_rtmp_relay_ctx_t));
    if (rctx == NULL) {
        goto clear;
    }

    if (name && ngx_rtmp_relay_copy_str(pool, &rctx->name, name) != NGX_OK) {
        goto clear;
    }

    if (ngx_rtmp_relay_copy_str(pool, &rctx->url, &target->url.url) != NGX_OK) {
        goto clear;
    }

    rctx->tag = target->tag;
    rctx->data = target->data;

#define NGX_RTMP_RELAY_STR_COPY(to, from)                                     \
    if (ngx_rtmp_relay_copy_str(pool, &rctx->to, &target->from) != NGX_OK) {  \
        goto clear;                                                           \
    }

    NGX_RTMP_RELAY_STR_COPY(app,        app);
    NGX_RTMP_RELAY_STR_COPY(tc_url,     tc_url);
    NGX_RTMP_RELAY_STR_COPY(page_url,   page_url);
    NGX_RTMP_RELAY_STR_COPY(swf_url,    swf_url);
    NGX_RTMP_RELAY_STR_COPY(flash_ver,  flash_ver);
    NGX_RTMP_RELAY_STR_COPY(play_path,  play_path);

    rctx->live  = target->live;
    rctx->start = target->start;
    rctx->stop  = target->stop;

#undef NGX_RTMP_RELAY_STR_COPY

    if (rctx->app.len == 0 || rctx->play_path.len == 0) {
        /* parse uri */
        uri = &target->url.uri;
        first = uri->data;
        last  = uri->data + uri->len;
        if (first != last && *first == '/') {
            ++first;
        }

        if (first != last) {

            /* deduce app */
            p = ngx_strlchr(first, last, '/');
            if (p == NULL) {
                p = last;
            }

            if (rctx->app.len == 0 && first != p) {
                v.data = first;
                v.len = p - first;
                if (ngx_rtmp_relay_copy_str(pool, &rctx->app, &v) != NGX_OK) {
                    goto clear;
                }
            }

            /* deduce play_path */
            if (p != last) {
                ++p;
            }

            if (rctx->play_path.len == 0 && p != last) {
                v.data = p;
                v.len = last - p;
                if (ngx_rtmp_relay_copy_str(pool, &rctx->play_path, &v)
                        != NGX_OK)
                {
                    goto clear;
                }
            }
        }
    }

    pc = ngx_pcalloc(pool, sizeof(ngx_peer_connection_t));
    if (pc == NULL) {
        goto clear;
    }

    if (target->url.naddrs == 0) {
        ngx_log_error(NGX_LOG_ERR, racf->log, 0,
                      "relay: no address");
        goto clear;
    }

    /* get address */
    addr = &target->url.addrs[target->counter % target->url.naddrs];
    target->counter++;

    /* copy log to keep shared log unchanged */
    rctx->log = *racf->log;
    pc->log = &rctx->log;
    pc->get = ngx_rtmp_relay_get_peer;
    pc->free = ngx_rtmp_relay_free_peer;
    pc->name = &addr->name;
    pc->socklen = addr->socklen;
    pc->sockaddr = (struct sockaddr *)ngx_palloc(pool, pc->socklen);
    if (pc->sockaddr == NULL) {
        goto clear;
    }
    ngx_memcpy(pc->sockaddr, addr->sockaddr, pc->socklen);

    rc = ngx_event_connect_peer(pc);
    if (rc != NGX_OK && rc != NGX_AGAIN ) {
        ngx_log_debug0(NGX_LOG_DEBUG_RTMP, racf->log, 0,
                "relay: connection failed");
        goto clear;
    }
    c = pc->connection;
    c->pool = pool;
    c->addr_text = rctx->url;

    addr_conf = ngx_pcalloc(pool, sizeof(ngx_rtmp_addr_conf_t));
    if (addr_conf == NULL) {
        goto clear;
    }
    addr_ctx = ngx_pcalloc(pool, sizeof(ngx_rtmp_conf_ctx_t));
    if (addr_ctx == NULL) {
        goto clear;
    }
    addr_conf->ctx = addr_ctx;
    addr_ctx->main_conf = cctx->main_conf;
    addr_ctx->srv_conf  = cctx->srv_conf;
    ngx_str_set(&addr_conf->addr_text, "ngx-relay");

    rs = ngx_rtmp_init_session(c, addr_conf);
    if (rs == NULL) {
        /* no need to destroy pool */
        return NULL;
    }
    rs->app_conf = cctx->app_conf;
    rs->relay = 1;
    rctx->session = rs;
    ngx_rtmp_set_ctx(rs, rctx, ngx_rtmp_relay_module);
    ngx_str_set(&rs->flashver, "ngx-local-relay");

#if (NGX_STAT_STUB)
    (void) ngx_atomic_fetch_add(ngx_stat_active, 1);
#endif

    ngx_rtmp_client_handshake(rs, 1);
    return rctx;

clear:
    if (pool) {
        ngx_destroy_pool(pool);
    }
    return NULL;
}