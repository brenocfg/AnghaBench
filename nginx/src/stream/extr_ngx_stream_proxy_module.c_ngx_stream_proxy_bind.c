#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
struct TYPE_20__ {int transparent; TYPE_13__* addr; TYPE_5__* value; } ;
typedef  TYPE_3__ ngx_stream_upstream_local_t ;
struct TYPE_21__ {TYPE_3__* local; } ;
typedef  TYPE_4__ ngx_stream_proxy_srv_conf_t ;
struct TYPE_22__ {scalar_t__ lengths; } ;
typedef  TYPE_5__ ngx_stream_complex_value_t ;
struct TYPE_23__ {TYPE_5__* complex_value; TYPE_7__* value; TYPE_9__* cf; } ;
typedef  TYPE_6__ ngx_stream_compile_complex_value_t ;
struct TYPE_24__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_7__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_25__ {int transparent; } ;
typedef  TYPE_8__ ngx_core_conf_t ;
struct TYPE_26__ {TYPE_2__* cycle; TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;
struct TYPE_19__ {int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_18__ {int nelts; TYPE_7__* elts; } ;
struct TYPE_17__ {TYPE_7__ name; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 TYPE_3__* NGX_CONF_UNSET_PTR ; 
#define  NGX_DECLINED 129 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
#define  NGX_OK 128 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int ngx_parse_addr_port (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_stream_compile_complex_value (TYPE_6__*) ; 

__attribute__((used)) static char *
ngx_stream_proxy_bind(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_proxy_srv_conf_t *pscf = conf;

    ngx_int_t                            rc;
    ngx_str_t                           *value;
    ngx_stream_complex_value_t           cv;
    ngx_stream_upstream_local_t         *local;
    ngx_stream_compile_complex_value_t   ccv;

    if (pscf->local != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (cf->args->nelts == 2 && ngx_strcmp(value[1].data, "off") == 0) {
        pscf->local = NULL;
        return NGX_CONF_OK;
    }

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &cv;

    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    local = ngx_pcalloc(cf->pool, sizeof(ngx_stream_upstream_local_t));
    if (local == NULL) {
        return NGX_CONF_ERROR;
    }

    pscf->local = local;

    if (cv.lengths) {
        local->value = ngx_palloc(cf->pool, sizeof(ngx_stream_complex_value_t));
        if (local->value == NULL) {
            return NGX_CONF_ERROR;
        }

        *local->value = cv;

    } else {
        local->addr = ngx_palloc(cf->pool, sizeof(ngx_addr_t));
        if (local->addr == NULL) {
            return NGX_CONF_ERROR;
        }

        rc = ngx_parse_addr_port(cf->pool, local->addr, value[1].data,
                                 value[1].len);

        switch (rc) {
        case NGX_OK:
            local->addr->name = value[1];
            break;

        case NGX_DECLINED:
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid address \"%V\"", &value[1]);
            /* fall through */

        default:
            return NGX_CONF_ERROR;
        }
    }

    if (cf->args->nelts > 2) {
        if (ngx_strcmp(value[2].data, "transparent") == 0) {
#if (NGX_HAVE_TRANSPARENT_PROXY)
            ngx_core_conf_t  *ccf;

            ccf = (ngx_core_conf_t *) ngx_get_conf(cf->cycle->conf_ctx,
                                                   ngx_core_module);

            ccf->transparent = 1;
            local->transparent = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "transparent proxying is not supported "
                               "on this platform, ignored");
#endif
        } else {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid parameter \"%V\"", &value[2]);
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}