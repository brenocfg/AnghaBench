#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t len; int /*<<< orphan*/  not_found; } ;
typedef  TYPE_1__ ngx_http_variable_value_t ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ ngx_http_script_var_code_t ;
struct TYPE_9__ {int /*<<< orphan*/  request; scalar_t__ flushed; scalar_t__ ip; } ;
typedef  TYPE_3__ ngx_http_script_engine_t ;

/* Variables and functions */
 TYPE_1__* ngx_http_get_flushed_variable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_get_indexed_variable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t
ngx_http_script_copy_var_len_code(ngx_http_script_engine_t *e)
{
    ngx_http_variable_value_t   *value;
    ngx_http_script_var_code_t  *code;

    code = (ngx_http_script_var_code_t *) e->ip;

    e->ip += sizeof(ngx_http_script_var_code_t);

    if (e->flushed) {
        value = ngx_http_get_indexed_variable(e->request, code->index);

    } else {
        value = ngx_http_get_flushed_variable(e->request, code->index);
    }

    if (value && !value->not_found) {
        return value->len;
    }

    return 0;
}