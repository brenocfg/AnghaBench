#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_22__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_25__ {int complete_lengths; int complete_values; int no_resolve; TYPE_2__ url; scalar_t__ variables; int /*<<< orphan*/ * values; scalar_t__* lengths; TYPE_6__* source; TYPE_10__* cf; } ;
typedef  TYPE_5__ ngx_url_t ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_26__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_6__ ngx_str_t ;
struct TYPE_23__ {int /*<<< orphan*/ * upstream; } ;
struct TYPE_27__ {int ssl; TYPE_3__ upstream; int /*<<< orphan*/  uwsgi_values; scalar_t__ uwsgi_lengths; } ;
typedef  TYPE_7__ ngx_http_uwsgi_loc_conf_t ;
typedef  TYPE_5__ ngx_http_script_compile_t ;
struct TYPE_24__ {int len; char* data; } ;
struct TYPE_28__ {int auto_redirect; TYPE_4__ name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_20__ {TYPE_1__* args; } ;
typedef  TYPE_10__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_21__ {TYPE_6__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__* ngx_http_conf_get_module_loc_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 scalar_t__ ngx_http_script_compile (TYPE_5__*) ; 
 scalar_t__ ngx_http_script_variables_count (TYPE_6__*) ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_10__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_uwsgi_handler ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 scalar_t__ ngx_strncasecmp (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_http_uwsgi_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_uwsgi_loc_conf_t *uwcf = conf;

    size_t                      add;
    ngx_url_t                   u;
    ngx_str_t                  *value, *url;
    ngx_uint_t                  n;
    ngx_http_core_loc_conf_t   *clcf;
    ngx_http_script_compile_t   sc;

    if (uwcf->upstream.upstream || uwcf->uwsgi_lengths) {
        return "is duplicate";
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_uwsgi_handler;

    value = cf->args->elts;

    url = &value[1];

    n = ngx_http_script_variables_count(url);

    if (n) {

        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

        sc.cf = cf;
        sc.source = url;
        sc.lengths = &uwcf->uwsgi_lengths;
        sc.values = &uwcf->uwsgi_values;
        sc.variables = n;
        sc.complete_lengths = 1;
        sc.complete_values = 1;

        if (ngx_http_script_compile(&sc) != NGX_OK) {
            return NGX_CONF_ERROR;
        }

#if (NGX_HTTP_SSL)
        uwcf->ssl = 1;
#endif

        return NGX_CONF_OK;
    }

    if (ngx_strncasecmp(url->data, (u_char *) "uwsgi://", 8) == 0) {
        add = 8;

    } else if (ngx_strncasecmp(url->data, (u_char *) "suwsgi://", 9) == 0) {

#if (NGX_HTTP_SSL)
        add = 9;
        uwcf->ssl = 1;
#else
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "suwsgi protocol requires SSL support");
        return NGX_CONF_ERROR;
#endif

    } else {
        add = 0;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url.len = url->len - add;
    u.url.data = url->data + add;
    u.no_resolve = 1;

    uwcf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
    if (uwcf->upstream.upstream == NULL) {
        return NGX_CONF_ERROR;
    }

    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {
        clcf->auto_redirect = 1;
    }

    return NGX_CONF_OK;
}