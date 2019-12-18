#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_25__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_27__ {void* (* create_loc_conf ) (TYPE_10__*) ;void* (* create_srv_conf ) (TYPE_10__*) ;} ;
typedef  TYPE_5__ ngx_http_module_t ;
struct TYPE_26__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_28__ {int socklen; int rcvbuf; int sndbuf; int setfib; int fastopen; int wildcard; struct sockaddr* sockaddr; TYPE_4__ addr_text; int /*<<< orphan*/  backlog; } ;
typedef  TYPE_6__ ngx_http_listen_opt_t ;
struct TYPE_29__ {int /*<<< orphan*/  listen; TYPE_9__* ctx; } ;
typedef  TYPE_7__ ngx_http_core_srv_conf_t ;
struct TYPE_30__ {int /*<<< orphan*/  servers; } ;
typedef  TYPE_8__ ngx_http_core_main_conf_t ;
struct TYPE_31__ {TYPE_8__** main_conf; TYPE_7__** srv_conf; void** loc_conf; } ;
typedef  TYPE_9__ ngx_http_conf_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  cmd_type; TYPE_9__* ctx; TYPE_2__* cycle; } ;
typedef  TYPE_10__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_24__ {TYPE_1__** modules; } ;
struct TYPE_23__ {scalar_t__ type; size_t ctx_index; TYPE_5__* ctx; } ;
struct TYPE_22__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int /*<<< orphan*/  NGX_HTTP_SRV_CONF ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LISTEN_BACKLOG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ getuid () ; 
 void* htons (int) ; 
 TYPE_7__** ngx_array_push (int /*<<< orphan*/ *) ; 
 char* ngx_conf_parse (TYPE_10__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_add_listen (TYPE_10__*,TYPE_7__*,TYPE_6__*) ; 
 TYPE_15__ ngx_http_core_module ; 
 int ngx_http_max_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_sock_ntop (struct sockaddr*,int,int /*<<< orphan*/ *,size_t,int) ; 
 void* stub1 (TYPE_10__*) ; 
 void* stub2 (TYPE_10__*) ; 

__attribute__((used)) static char *
ngx_http_core_server(ngx_conf_t *cf, ngx_command_t *cmd, void *dummy)
{
    char                        *rv;
    void                        *mconf;
    size_t                       len;
    u_char                      *p;
    ngx_uint_t                   i;
    ngx_conf_t                   pcf;
    ngx_http_module_t           *module;
    struct sockaddr_in          *sin;
    ngx_http_conf_ctx_t         *ctx, *http_ctx;
    ngx_http_listen_opt_t        lsopt;
    ngx_http_core_srv_conf_t    *cscf, **cscfp;
    ngx_http_core_main_conf_t   *cmcf;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_http_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    http_ctx = cf->ctx;
    ctx->main_conf = http_ctx->main_conf;

    /* the server{}'s srv_conf */

    ctx->srv_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    /* the server{}'s loc_conf */

    ctx->loc_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->loc_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    for (i = 0; cf->cycle->modules[i]; i++) {
        if (cf->cycle->modules[i]->type != NGX_HTTP_MODULE) {
            continue;
        }

        module = cf->cycle->modules[i]->ctx;

        if (module->create_srv_conf) {
            mconf = module->create_srv_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->srv_conf[cf->cycle->modules[i]->ctx_index] = mconf;
        }

        if (module->create_loc_conf) {
            mconf = module->create_loc_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->loc_conf[cf->cycle->modules[i]->ctx_index] = mconf;
        }
    }


    /* the server configuration context */

    cscf = ctx->srv_conf[ngx_http_core_module.ctx_index];
    cscf->ctx = ctx;


    cmcf = ctx->main_conf[ngx_http_core_module.ctx_index];

    cscfp = ngx_array_push(&cmcf->servers);
    if (cscfp == NULL) {
        return NGX_CONF_ERROR;
    }

    *cscfp = cscf;


    /* parse inside server{} */

    pcf = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_HTTP_SRV_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pcf;

    if (rv == NGX_CONF_OK && !cscf->listen) {
        ngx_memzero(&lsopt, sizeof(ngx_http_listen_opt_t));

        p = ngx_pcalloc(cf->pool, sizeof(struct sockaddr_in));
        if (p == NULL) {
            return NGX_CONF_ERROR;
        }

        lsopt.sockaddr = (struct sockaddr *) p;

        sin = (struct sockaddr_in *) p;

        sin->sin_family = AF_INET;
#if (NGX_WIN32)
        sin->sin_port = htons(80);
#else
        sin->sin_port = htons((getuid() == 0) ? 80 : 8000);
#endif
        sin->sin_addr.s_addr = INADDR_ANY;

        lsopt.socklen = sizeof(struct sockaddr_in);

        lsopt.backlog = NGX_LISTEN_BACKLOG;
        lsopt.rcvbuf = -1;
        lsopt.sndbuf = -1;
#if (NGX_HAVE_SETFIB)
        lsopt.setfib = -1;
#endif
#if (NGX_HAVE_TCP_FASTOPEN)
        lsopt.fastopen = -1;
#endif
        lsopt.wildcard = 1;

        len = NGX_INET_ADDRSTRLEN + sizeof(":65535") - 1;

        p = ngx_pnalloc(cf->pool, len);
        if (p == NULL) {
            return NGX_CONF_ERROR;
        }

        lsopt.addr_text.data = p;
        lsopt.addr_text.len = ngx_sock_ntop(lsopt.sockaddr, lsopt.socklen, p,
                                            len, 1);

        if (ngx_http_add_listen(cf, cscf, &lsopt) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    return rv;
}