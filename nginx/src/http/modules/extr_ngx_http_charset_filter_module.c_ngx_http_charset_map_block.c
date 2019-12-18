#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  void* u_char ;
typedef  int ngx_uint_t ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {scalar_t__ src; scalar_t__ dst; void** src2dst; char* dst2src; } ;
typedef  TYPE_3__ ngx_http_charset_tables_t ;
struct TYPE_21__ {int length; } ;
typedef  TYPE_4__ ngx_http_charset_t ;
struct TYPE_25__ {TYPE_4__* elts; } ;
struct TYPE_17__ {int nelts; TYPE_3__* elts; } ;
struct TYPE_22__ {TYPE_9__ charsets; TYPE_16__ tables; } ;
typedef  TYPE_5__ ngx_http_charset_main_conf_t ;
struct TYPE_23__ {int characters; TYPE_4__* charset; TYPE_3__* table; } ;
typedef  TYPE_6__ ngx_http_charset_conf_ctx_t ;
struct TYPE_24__ {void* handler_conf; int /*<<< orphan*/  handler; TYPE_6__* ctx; int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_18__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int NGX_UTF_LEN ; 
 TYPE_3__* ngx_array_push (TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,TYPE_2__*,TYPE_2__*) ; 
 char* ngx_conf_parse (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_add_charset (TYPE_9__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_charset_map ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcasecmp (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static char *
ngx_http_charset_map_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_charset_main_conf_t  *mcf = conf;

    char                         *rv;
    u_char                       *p, *dst2src, **pp;
    ngx_int_t                     src, dst;
    ngx_uint_t                    i, n;
    ngx_str_t                    *value;
    ngx_conf_t                    pvcf;
    ngx_http_charset_t           *charset;
    ngx_http_charset_tables_t    *table;
    ngx_http_charset_conf_ctx_t   ctx;

    value = cf->args->elts;

    src = ngx_http_add_charset(&mcf->charsets, &value[1]);
    if (src == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    dst = ngx_http_add_charset(&mcf->charsets, &value[2]);
    if (dst == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    if (src == dst) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"charset_map\" between the same charsets "
                           "\"%V\" and \"%V\"", &value[1], &value[2]);
        return NGX_CONF_ERROR;
    }

    table = mcf->tables.elts;
    for (i = 0; i < mcf->tables.nelts; i++) {
        if ((src == table->src && dst == table->dst)
             || (src == table->dst && dst == table->src))
        {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "duplicate \"charset_map\" between "
                               "\"%V\" and \"%V\"", &value[1], &value[2]);
            return NGX_CONF_ERROR;
        }
    }

    table = ngx_array_push(&mcf->tables);
    if (table == NULL) {
        return NGX_CONF_ERROR;
    }

    table->src = src;
    table->dst = dst;

    if (ngx_strcasecmp(value[2].data, (u_char *) "utf-8") == 0) {
        table->src2dst = ngx_pcalloc(cf->pool, 256 * NGX_UTF_LEN);
        if (table->src2dst == NULL) {
            return NGX_CONF_ERROR;
        }

        table->dst2src = ngx_pcalloc(cf->pool, 256 * sizeof(void *));
        if (table->dst2src == NULL) {
            return NGX_CONF_ERROR;
        }

        dst2src = ngx_pcalloc(cf->pool, 256);
        if (dst2src == NULL) {
            return NGX_CONF_ERROR;
        }

        pp = (u_char **) &table->dst2src[0];
        pp[0] = dst2src;

        for (i = 0; i < 128; i++) {
            p = &table->src2dst[i * NGX_UTF_LEN];
            p[0] = '\1';
            p[1] = (u_char) i;
            dst2src[i] = (u_char) i;
        }

        for (/* void */; i < 256; i++) {
            p = &table->src2dst[i * NGX_UTF_LEN];
            p[0] = '\1';
            p[1] = '?';
        }

    } else {
        table->src2dst = ngx_palloc(cf->pool, 256);
        if (table->src2dst == NULL) {
            return NGX_CONF_ERROR;
        }

        table->dst2src = ngx_palloc(cf->pool, 256);
        if (table->dst2src == NULL) {
            return NGX_CONF_ERROR;
        }

        for (i = 0; i < 128; i++) {
            table->src2dst[i] = (u_char) i;
            table->dst2src[i] = (u_char) i;
        }

        for (/* void */; i < 256; i++) {
            table->src2dst[i] = '?';
            table->dst2src[i] = '?';
        }
    }

    charset = mcf->charsets.elts;

    ctx.table = table;
    ctx.charset = &charset[dst];
    ctx.characters = 0;

    pvcf = *cf;
    cf->ctx = &ctx;
    cf->handler = ngx_http_charset_map;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pvcf;

    if (ctx.characters) {
        n = ctx.charset->length;
        ctx.charset->length /= ctx.characters;

        if (((n * 10) / ctx.characters) % 10 > 4) {
            ctx.charset->length++;
        }
    }

    return rv;
}