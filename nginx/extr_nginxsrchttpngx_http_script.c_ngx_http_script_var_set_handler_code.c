#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ngx_http_script_var_handler_code_t ;
struct TYPE_8__ {int /*<<< orphan*/  sp; TYPE_4__* request; scalar_t__ ip; } ;
typedef  TYPE_3__ ngx_http_script_engine_t ;
struct TYPE_9__ {TYPE_1__* connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ngx_http_script_var_set_handler_code(ngx_http_script_engine_t *e)
{
    ngx_http_script_var_handler_code_t  *code;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, e->request->connection->log, 0,
                   "http script set var handler");

    code = (ngx_http_script_var_handler_code_t *) e->ip;

    e->ip += sizeof(ngx_http_script_var_handler_code_t);

    e->sp--;

    code->handler(e->request, e->sp, code->data);
}