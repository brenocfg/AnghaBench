#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_15__ {scalar_t__ outside_entries; int /*<<< orphan*/  includes; scalar_t__ allow_binary_include; TYPE_1__ include_name; scalar_t__ ranges; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_2__ ngx_http_geo_conf_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; int /*<<< orphan*/  cycle; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
#define  NGX_ERROR 129 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
#define  NGX_OK 128 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 char* ngx_conf_parse (TYPE_3__*,TYPE_1__*) ; 
 int ngx_http_geo_include_binary_base (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_sprintf (char*,char*,TYPE_1__*) ; 

__attribute__((used)) static char *
ngx_http_geo_include(ngx_conf_t *cf, ngx_http_geo_conf_ctx_t *ctx,
    ngx_str_t *name)
{
    char       *rv;
    ngx_str_t   file;

    file.len = name->len + 4;
    file.data = ngx_pnalloc(ctx->temp_pool, name->len + 5);
    if (file.data == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_sprintf(file.data, "%V.bin%Z", name);

    if (ngx_conf_full_name(cf->cycle, &file, 1) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ctx->ranges) {
        ngx_log_debug1(NGX_LOG_DEBUG_CORE, cf->log, 0, "include %s", file.data);

        switch (ngx_http_geo_include_binary_base(cf, ctx, &file)) {
        case NGX_OK:
            return NGX_CONF_OK;
        case NGX_ERROR:
            return NGX_CONF_ERROR;
        default:
            break;
        }
    }

    file.len -= 4;
    file.data[file.len] = '\0';

    ctx->include_name = file;

    if (ctx->outside_entries) {
        ctx->allow_binary_include = 0;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_CORE, cf->log, 0, "include %s", file.data);

    rv = ngx_conf_parse(cf, &file);

    ctx->includes++;
    ctx->outside_entries = 0;

    return rv;
}