#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int complete_lengths; int complete_values; int no_resolve; int /*<<< orphan*/  url; scalar_t__ variables; int /*<<< orphan*/ * values; scalar_t__* lengths; int /*<<< orphan*/ * source; TYPE_8__* cf; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  TYPE_4__ ngx_http_script_compile_t ;
struct TYPE_17__ {int /*<<< orphan*/ * upstream; } ;
struct TYPE_20__ {TYPE_2__ upstream; int /*<<< orphan*/  scgi_values; scalar_t__ scgi_lengths; } ;
typedef  TYPE_6__ ngx_http_scgi_loc_conf_t ;
struct TYPE_18__ {int len; char* data; } ;
struct TYPE_21__ {int auto_redirect; TYPE_3__ name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_22__ {TYPE_1__* args; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_16__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 TYPE_7__* ngx_http_conf_get_module_loc_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_scgi_handler ; 
 scalar_t__ ngx_http_script_compile (TYPE_4__*) ; 
 scalar_t__ ngx_http_script_variables_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 

__attribute__((used)) static char *
ngx_http_scgi_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_scgi_loc_conf_t *scf = conf;

    ngx_url_t                   u;
    ngx_str_t                  *value, *url;
    ngx_uint_t                  n;
    ngx_http_core_loc_conf_t   *clcf;
    ngx_http_script_compile_t   sc;

    if (scf->upstream.upstream || scf->scgi_lengths) {
        return "is duplicate";
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_scgi_handler;

    value = cf->args->elts;

    url = &value[1];

    n = ngx_http_script_variables_count(url);

    if (n) {

        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

        sc.cf = cf;
        sc.source = url;
        sc.lengths = &scf->scgi_lengths;
        sc.values = &scf->scgi_values;
        sc.variables = n;
        sc.complete_lengths = 1;
        sc.complete_values = 1;

        if (ngx_http_script_compile(&sc) != NGX_OK) {
            return NGX_CONF_ERROR;
        }

        return NGX_CONF_OK;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url = value[1];
    u.no_resolve = 1;

    scf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
    if (scf->upstream.upstream == NULL) {
        return NGX_CONF_ERROR;
    }

    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {
        clcf->auto_redirect = 1;
    }

    return NGX_CONF_OK;
}