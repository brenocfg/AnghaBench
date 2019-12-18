#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_18__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {TYPE_2__ value; int /*<<< orphan*/ * lengths; } ;
struct TYPE_21__ {TYPE_3__ value; TYPE_3__ match; } ;
typedef  TYPE_5__ ngx_http_sub_pair_t ;
struct TYPE_22__ {int dynamic; TYPE_14__* pairs; } ;
typedef  TYPE_6__ ngx_http_sub_loc_conf_t ;
struct TYPE_23__ {TYPE_3__* complex_value; TYPE_4__* value; TYPE_8__* cf; } ;
typedef  TYPE_7__ ngx_http_compile_complex_value_t ;
struct TYPE_24__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_17__ {TYPE_4__* elts; } ;
struct TYPE_16__ {int nelts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 TYPE_14__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (TYPE_14__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_http_compile_complex_value (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static char *
ngx_http_sub_filter(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_sub_loc_conf_t *slcf = conf;

    ngx_str_t                         *value;
    ngx_http_sub_pair_t               *pair;
    ngx_http_compile_complex_value_t   ccv;

    value = cf->args->elts;

    if (value[1].len == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "empty search pattern");
        return NGX_CONF_ERROR;
    }

    if (slcf->pairs == NULL) {
        slcf->pairs = ngx_array_create(cf->pool, 1,
                                       sizeof(ngx_http_sub_pair_t));
        if (slcf->pairs == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    if (slcf->pairs->nelts == 255) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "number of search patterns exceeds 255");
        return NGX_CONF_ERROR;
    }

    ngx_strlow(value[1].data, value[1].data, value[1].len);

    pair = ngx_array_push(slcf->pairs);
    if (pair == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &pair->match;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ccv.complex_value->lengths != NULL) {
        slcf->dynamic = 1;

    } else {
        ngx_strlow(pair->match.value.data, pair->match.value.data,
                   pair->match.value.len);
    }

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[2];
    ccv.complex_value = &pair->value;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}