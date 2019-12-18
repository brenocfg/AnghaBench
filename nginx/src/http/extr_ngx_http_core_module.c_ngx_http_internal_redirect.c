#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {scalar_t__ uri_changes; int internal; TYPE_3__* main; scalar_t__ add_uri_to_alias; scalar_t__ valid_unparsed_uri; int /*<<< orphan*/ * cache; int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  ctx; void* args; TYPE_1__* connection; void* uri; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {TYPE_2__* ctx; } ;
typedef  TYPE_5__ ngx_http_core_srv_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  count; } ;
struct TYPE_14__ {int /*<<< orphan*/  loc_conf; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_handler (TYPE_4__*) ; 
 int ngx_http_max_module ; 
 int /*<<< orphan*/  ngx_http_set_exten (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_update_location_config (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**,void**) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  ngx_memzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_null (void**) ; 

ngx_int_t
ngx_http_internal_redirect(ngx_http_request_t *r,
    ngx_str_t *uri, ngx_str_t *args)
{
    ngx_http_core_srv_conf_t  *cscf;

    r->uri_changes--;

    if (r->uri_changes == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "rewrite or internal redirection cycle "
                      "while internally redirecting to \"%V\"", uri);

        r->main->count++;
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return NGX_DONE;
    }

    r->uri = *uri;

    if (args) {
        r->args = *args;

    } else {
        ngx_str_null(&r->args);
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "internal redirect: \"%V?%V\"", uri, &r->args);

    ngx_http_set_exten(r);

    /* clear the modules contexts */
    ngx_memzero(r->ctx, sizeof(void *) * ngx_http_max_module);

    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);
    r->loc_conf = cscf->ctx->loc_conf;

    ngx_http_update_location_config(r);

#if (NGX_HTTP_CACHE)
    r->cache = NULL;
#endif

    r->internal = 1;
    r->valid_unparsed_uri = 0;
    r->add_uri_to_alias = 0;
    r->main->count++;

    ngx_http_handler(r);

    return NGX_DONE;
}