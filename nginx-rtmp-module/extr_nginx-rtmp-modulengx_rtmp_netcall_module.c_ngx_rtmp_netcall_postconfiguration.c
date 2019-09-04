#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_handler_pt ;
struct TYPE_3__ {int /*<<< orphan*/ * events; } ;
typedef  TYPE_1__ ngx_rtmp_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 size_t NGX_RTMP_DISCONNECT ; 
 int /*<<< orphan*/ * ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_rtmp_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_disconnect ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_netcall_postconfiguration(ngx_conf_t *cf)
{
    ngx_rtmp_core_main_conf_t          *cmcf;
    ngx_rtmp_handler_pt                *h;

    cmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_core_module);

    h = ngx_array_push(&cmcf->events[NGX_RTMP_DISCONNECT]);
    *h = ngx_rtmp_netcall_disconnect;

    return NGX_OK;
}