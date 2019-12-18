#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
typedef  int /*<<< orphan*/  (* ngx_stream_handler_pt ) (int /*<<< orphan*/ *) ;
struct TYPE_7__ {TYPE_2__* phases; } ;
typedef  TYPE_3__ ngx_stream_core_main_conf_t ;
struct TYPE_5__ {size_t nelts; int /*<<< orphan*/  (* elts ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 size_t NGX_STREAM_LOG_PHASE ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 TYPE_3__* ngx_stream_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_stream_log_session(ngx_stream_session_t *s)
{
    ngx_uint_t                    i, n;
    ngx_stream_handler_pt        *log_handler;
    ngx_stream_core_main_conf_t  *cmcf;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    log_handler = cmcf->phases[NGX_STREAM_LOG_PHASE].handlers.elts;
    n = cmcf->phases[NGX_STREAM_LOG_PHASE].handlers.nelts;

    for (i = 0; i < n; i++) {
        log_handler[i](s);
    }
}