#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
typedef  scalar_t__ (* ngx_rtmp_handler_pt ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_4__ {TYPE_2__* events; } ;
typedef  TYPE_1__ ngx_rtmp_core_main_conf_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_5__ {scalar_t__ (* elts ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;size_t nelts; } ;
typedef  TYPE_2__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_1__* ngx_rtmp_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_fire_event(ngx_rtmp_session_t *s, ngx_uint_t evt,
        ngx_rtmp_header_t *h, ngx_chain_t *in)
{
    ngx_rtmp_core_main_conf_t      *cmcf;
    ngx_array_t                    *ch;
    ngx_rtmp_handler_pt            *hh;
    size_t                          n;

    cmcf = ngx_rtmp_get_module_main_conf(s, ngx_rtmp_core_module);

    ch = &cmcf->events[evt];
    hh = ch->elts;
    for(n = 0; n < ch->nelts; ++n, ++hh) {
        if (*hh && (*hh)(s, h, in) != NGX_OK) {
            return NGX_ERROR;
        }
    }
    return NGX_OK;
}