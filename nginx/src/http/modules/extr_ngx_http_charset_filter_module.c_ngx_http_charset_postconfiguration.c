#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
typedef  size_t ngx_int_t ;
struct TYPE_15__ {size_t src; size_t dst; int /*<<< orphan*/ * dst2src; int /*<<< orphan*/ * src2dst; } ;
typedef  TYPE_4__ ngx_http_charset_tables_t ;
struct TYPE_16__ {int /*<<< orphan*/ ** tables; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ ngx_http_charset_t ;
struct TYPE_17__ {size_t src; size_t dst; } ;
typedef  TYPE_6__ ngx_http_charset_recode_t ;
struct TYPE_14__ {int nelts; TYPE_5__* elts; } ;
struct TYPE_13__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_12__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_18__ {TYPE_3__ charsets; TYPE_2__ tables; TYPE_1__ recodes; } ;
typedef  TYPE_7__ ngx_http_charset_main_conf_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_8__ ngx_conf_t ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 size_t NGX_OK ; 
 int /*<<< orphan*/  ngx_http_charset_body_filter ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 int /*<<< orphan*/  ngx_http_charset_header_filter ; 
 TYPE_7__* ngx_http_conf_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_body_filter ; 
 int /*<<< orphan*/  ngx_http_next_header_filter ; 
 int /*<<< orphan*/  ngx_http_top_body_filter ; 
 int /*<<< orphan*/  ngx_http_top_header_filter ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_charset_postconfiguration(ngx_conf_t *cf)
{
    u_char                       **src, **dst;
    ngx_int_t                      c;
    ngx_uint_t                     i, t;
    ngx_http_charset_t            *charset;
    ngx_http_charset_recode_t     *recode;
    ngx_http_charset_tables_t     *tables;
    ngx_http_charset_main_conf_t  *mcf;

    mcf = ngx_http_conf_get_module_main_conf(cf,
                                             ngx_http_charset_filter_module);

    recode = mcf->recodes.elts;
    tables = mcf->tables.elts;
    charset = mcf->charsets.elts;

    for (i = 0; i < mcf->recodes.nelts; i++) {

        c = recode[i].src;

        for (t = 0; t < mcf->tables.nelts; t++) {

            if (c == tables[t].src && recode[i].dst == tables[t].dst) {
                goto next;
            }

            if (c == tables[t].dst && recode[i].dst == tables[t].src) {
                goto next;
            }
        }

        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                   "no \"charset_map\" between the charsets \"%V\" and \"%V\"",
                   &charset[c].name, &charset[recode[i].dst].name);
        return NGX_ERROR;

    next:
        continue;
    }


    for (t = 0; t < mcf->tables.nelts; t++) {

        src = charset[tables[t].src].tables;

        if (src == NULL) {
            src = ngx_pcalloc(cf->pool, sizeof(u_char *) * mcf->charsets.nelts);
            if (src == NULL) {
                return NGX_ERROR;
            }

            charset[tables[t].src].tables = src;
        }

        dst = charset[tables[t].dst].tables;

        if (dst == NULL) {
            dst = ngx_pcalloc(cf->pool, sizeof(u_char *) * mcf->charsets.nelts);
            if (dst == NULL) {
                return NGX_ERROR;
            }

            charset[tables[t].dst].tables = dst;
        }

        src[tables[t].dst] = tables[t].src2dst;
        dst[tables[t].src] = tables[t].dst2src;
    }

    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_charset_header_filter;

    ngx_http_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_charset_body_filter;

    return NGX_OK;
}