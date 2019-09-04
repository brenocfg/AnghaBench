#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {uintptr_t value; uintptr_t text_len; uintptr_t text_data; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ ngx_http_script_value_code_t ;
struct TYPE_15__ {int /*<<< orphan*/ * lengths; int /*<<< orphan*/  code; } ;
typedef  TYPE_3__ ngx_http_script_complex_value_code_t ;
struct TYPE_16__ {int complete_lengths; scalar_t__ variables; int /*<<< orphan*/ * values; int /*<<< orphan*/ ** lengths; TYPE_1__* source; TYPE_6__* cf; } ;
typedef  TYPE_4__ ngx_http_script_compile_t ;
struct TYPE_17__ {int /*<<< orphan*/  codes; } ;
typedef  TYPE_5__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_atoi (scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_http_script_compile (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_script_complex_value_code ; 
 void* ngx_http_script_start_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_script_value_code ; 
 scalar_t__ ngx_http_script_variables_count (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 

__attribute__((used)) static char *
ngx_http_rewrite_value(ngx_conf_t *cf, ngx_http_rewrite_loc_conf_t *lcf,
    ngx_str_t *value)
{
    ngx_int_t                              n;
    ngx_http_script_compile_t              sc;
    ngx_http_script_value_code_t          *val;
    ngx_http_script_complex_value_code_t  *complex;

    n = ngx_http_script_variables_count(value);

    if (n == 0) {
        val = ngx_http_script_start_code(cf->pool, &lcf->codes,
                                         sizeof(ngx_http_script_value_code_t));
        if (val == NULL) {
            return NGX_CONF_ERROR;
        }

        n = ngx_atoi(value->data, value->len);

        if (n == NGX_ERROR) {
            n = 0;
        }

        val->code = ngx_http_script_value_code;
        val->value = (uintptr_t) n;
        val->text_len = (uintptr_t) value->len;
        val->text_data = (uintptr_t) value->data;

        return NGX_CONF_OK;
    }

    complex = ngx_http_script_start_code(cf->pool, &lcf->codes,
                                 sizeof(ngx_http_script_complex_value_code_t));
    if (complex == NULL) {
        return NGX_CONF_ERROR;
    }

    complex->code = ngx_http_script_complex_value_code;
    complex->lengths = NULL;

    ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

    sc.cf = cf;
    sc.source = value;
    sc.lengths = &complex->lengths;
    sc.values = &lcf->codes;
    sc.variables = n;
    sc.complete_lengths = 1;

    if (ngx_http_script_compile(&sc) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}