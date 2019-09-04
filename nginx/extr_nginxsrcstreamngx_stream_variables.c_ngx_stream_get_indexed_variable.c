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
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int not_found; int no_cacheable; scalar_t__ valid; } ;
typedef  TYPE_3__ ngx_stream_variable_value_t ;
struct TYPE_16__ {scalar_t__ (* get_handler ) (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ;int flags; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ ngx_stream_variable_t ;
struct TYPE_17__ {TYPE_3__* variables; TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
struct TYPE_13__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_18__ {TYPE_1__ variables; } ;
typedef  TYPE_6__ ngx_stream_core_main_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int NGX_STREAM_VAR_NOCACHEABLE ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 TYPE_6__* ngx_stream_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_variable_depth ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

ngx_stream_variable_value_t *
ngx_stream_get_indexed_variable(ngx_stream_session_t *s, ngx_uint_t index)
{
    ngx_stream_variable_t        *v;
    ngx_stream_core_main_conf_t  *cmcf;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    if (cmcf->variables.nelts <= index) {
        ngx_log_error(NGX_LOG_ALERT, s->connection->log, 0,
                      "unknown variable index: %ui", index);
        return NULL;
    }

    if (s->variables[index].not_found || s->variables[index].valid) {
        return &s->variables[index];
    }

    v = cmcf->variables.elts;

    if (ngx_stream_variable_depth == 0) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "cycle while evaluating variable \"%V\"",
                      &v[index].name);
        return NULL;
    }

    ngx_stream_variable_depth--;

    if (v[index].get_handler(s, &s->variables[index], v[index].data)
        == NGX_OK)
    {
        ngx_stream_variable_depth++;

        if (v[index].flags & NGX_STREAM_VAR_NOCACHEABLE) {
            s->variables[index].no_cacheable = 1;
        }

        return &s->variables[index];
    }

    ngx_stream_variable_depth++;

    s->variables[index].valid = 0;
    s->variables[index].not_found = 1;

    return NULL;
}