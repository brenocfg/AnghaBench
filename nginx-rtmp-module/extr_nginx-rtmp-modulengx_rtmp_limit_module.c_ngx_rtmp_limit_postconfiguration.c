#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ max_conn; TYPE_3__* shm_zone; } ;
typedef  TYPE_1__ ngx_rtmp_limit_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_handler_pt ;
struct TYPE_5__ {int /*<<< orphan*/ * events; } ;
typedef  TYPE_2__ ngx_rtmp_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  init; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 size_t NGX_RTMP_CONNECT ; 
 size_t NGX_RTMP_DISCONNECT ; 
 int /*<<< orphan*/ * ngx_array_push (int /*<<< orphan*/ *) ; 
 int ngx_pagesize ; 
 void* ngx_rtmp_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_limit_connect ; 
 int /*<<< orphan*/  ngx_rtmp_limit_disconnect ; 
 int /*<<< orphan*/  ngx_rtmp_limit_module ; 
 int /*<<< orphan*/  ngx_rtmp_limit_shm_init ; 
 TYPE_3__* ngx_shared_memory_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_name ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_limit_postconfiguration(ngx_conf_t *cf)
{
    ngx_rtmp_core_main_conf_t  *cmcf;
    ngx_rtmp_limit_main_conf_t *lmcf;
    ngx_rtmp_handler_pt        *h;

    cmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_core_module);

    h = ngx_array_push(&cmcf->events[NGX_RTMP_CONNECT]);
    *h = ngx_rtmp_limit_connect;

    h = ngx_array_push(&cmcf->events[NGX_RTMP_DISCONNECT]);
    *h = ngx_rtmp_limit_disconnect;

    lmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_limit_module);
    if (lmcf->max_conn == NGX_CONF_UNSET) {
        return NGX_OK;
    }

    lmcf->shm_zone = ngx_shared_memory_add(cf, &shm_name, ngx_pagesize * 2,
                                           &ngx_rtmp_limit_module);
    if (lmcf->shm_zone == NULL) {
        return NGX_ERROR;
    }

    lmcf->shm_zone->init = ngx_rtmp_limit_shm_init;

    return NGX_OK;
}