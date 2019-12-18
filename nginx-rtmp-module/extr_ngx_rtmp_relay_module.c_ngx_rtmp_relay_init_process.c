#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_24__ {TYPE_7__** app_conf; } ;
struct TYPE_25__ {TYPE_5__ cctx; } ;
typedef  TYPE_6__ ngx_rtmp_relay_static_t ;
struct TYPE_23__ {scalar_t__ nelts; TYPE_12__** elts; } ;
struct TYPE_26__ {TYPE_4__ static_events; } ;
typedef  TYPE_7__ ngx_rtmp_relay_app_conf_t ;
struct TYPE_27__ {TYPE_5__* ctx; } ;
typedef  TYPE_8__ ngx_rtmp_listen_t ;
struct TYPE_22__ {scalar_t__ nelts; TYPE_11__** elts; } ;
struct TYPE_28__ {TYPE_3__ applications; } ;
typedef  TYPE_9__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_21__ {scalar_t__ nelts; TYPE_9__** elts; } ;
struct TYPE_20__ {scalar_t__ nelts; TYPE_8__* elts; } ;
struct TYPE_16__ {TYPE_2__ servers; TYPE_1__ listen; } ;
typedef  TYPE_10__ ngx_rtmp_core_main_conf_t ;
struct TYPE_17__ {TYPE_7__** app_conf; } ;
typedef  TYPE_11__ ngx_rtmp_core_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {TYPE_6__* data; } ;
typedef  TYPE_12__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_19__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_12__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_process_slot ; 
 TYPE_10__* ngx_rtmp_core_main_conf ; 
 int /*<<< orphan*/  ngx_rtmp_init_queue ; 
 TYPE_13__ ngx_rtmp_relay_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_relay_init_process(ngx_cycle_t *cycle)
{
#if !(NGX_WIN32)
    ngx_rtmp_core_main_conf_t  *cmcf = ngx_rtmp_core_main_conf;
    ngx_rtmp_core_srv_conf_t  **pcscf, *cscf;
    ngx_rtmp_core_app_conf_t  **pcacf, *cacf;
    ngx_rtmp_relay_app_conf_t  *racf;
    ngx_uint_t                  n, m, k;
    ngx_rtmp_relay_static_t    *rs;
    ngx_rtmp_listen_t          *lst;
    ngx_event_t               **pevent, *event;

    if (cmcf == NULL || cmcf->listen.nelts == 0) {
        return NGX_OK;
    }

    /* only first worker does static pulling */

    if (ngx_process_slot) {
        return NGX_OK;
    }

    lst = cmcf->listen.elts;

    pcscf = cmcf->servers.elts;
    for (n = 0; n < cmcf->servers.nelts; ++n, ++pcscf) {

        cscf = *pcscf;
        pcacf = cscf->applications.elts;

        for (m = 0; m < cscf->applications.nelts; ++m, ++pcacf) {

            cacf = *pcacf;
            racf = cacf->app_conf[ngx_rtmp_relay_module.ctx_index];
            pevent = racf->static_events.elts;

            for (k = 0; k < racf->static_events.nelts; ++k, ++pevent) {
                event = *pevent;

                rs = event->data;
                rs->cctx = *lst->ctx;
                rs->cctx.app_conf = cacf->app_conf;

                ngx_post_event(event, &ngx_rtmp_init_queue);
            }
        }
    }
#endif
    return NGX_OK;
}