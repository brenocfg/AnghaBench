#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int preserve_body; int /*<<< orphan*/  (* write_event_handler ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ ngx_http_mirror_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_1__*) ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mirror_handler_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_mirror_module ; 

__attribute__((used)) static void
ngx_http_mirror_body_handler(ngx_http_request_t *r)
{
    ngx_http_mirror_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_mirror_module);

    ctx->status = ngx_http_mirror_handler_internal(r);

    r->preserve_body = 1;

    r->write_event_handler = ngx_http_core_run_phases;
    ngx_http_core_run_phases(r);
}