#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  not_found; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_3__ ngx_http_script_var_code_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pos; TYPE_7__* request; scalar_t__ flushed; int /*<<< orphan*/  skip; scalar_t__ ip; } ;
typedef  TYPE_4__ ngx_http_script_engine_t ;
struct TYPE_14__ {TYPE_1__* connection; } ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_flushed_variable (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_indexed_variable (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

void
ngx_http_script_copy_var_code(ngx_http_script_engine_t *e)
{
    u_char                      *p;
    ngx_http_variable_value_t   *value;
    ngx_http_script_var_code_t  *code;

    code = (ngx_http_script_var_code_t *) e->ip;

    e->ip += sizeof(ngx_http_script_var_code_t);

    if (!e->skip) {

        if (e->flushed) {
            value = ngx_http_get_indexed_variable(e->request, code->index);

        } else {
            value = ngx_http_get_flushed_variable(e->request, code->index);
        }

        if (value && !value->not_found) {
            p = e->pos;
            e->pos = ngx_copy(p, value->data, value->len);

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP,
                           e->request->connection->log, 0,
                           "http script var: \"%*s\"", e->pos - p, p);
        }
    }
}