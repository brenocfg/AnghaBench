#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_handler_pt ;
struct TYPE_5__ {int /*<<< orphan*/  amf; int /*<<< orphan*/ * events; } ;
typedef  TYPE_1__ ngx_rtmp_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_handler_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_MAX_EVENT ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_init_events(ngx_conf_t *cf, ngx_rtmp_core_main_conf_t *cmcf)
{
    size_t                      n;

    for(n = 0; n < NGX_RTMP_MAX_EVENT; ++n) {
        if (ngx_array_init(&cmcf->events[n], cf->pool, 1,
                sizeof(ngx_rtmp_handler_pt)) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    if (ngx_array_init(&cmcf->amf, cf->pool, 1,
                sizeof(ngx_rtmp_amf_handler_t)) != NGX_OK)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}