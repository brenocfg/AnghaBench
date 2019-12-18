#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t phase_handler; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
struct TYPE_12__ {scalar_t__ (* checker ) (TYPE_2__*,TYPE_3__*) ;} ;
typedef  TYPE_3__ ngx_stream_phase_handler_t ;
struct TYPE_10__ {TYPE_3__* handlers; } ;
struct TYPE_13__ {TYPE_1__ phase_engine; } ;
typedef  TYPE_4__ ngx_stream_core_main_conf_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 TYPE_4__* ngx_stream_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_3__*) ; 

void
ngx_stream_core_run_phases(ngx_stream_session_t *s)
{
    ngx_int_t                     rc;
    ngx_stream_phase_handler_t   *ph;
    ngx_stream_core_main_conf_t  *cmcf;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    ph = cmcf->phase_engine.handlers;

    while (ph[s->phase_handler].checker) {

        rc = ph[s->phase_handler].checker(s, &ph[s->phase_handler]);

        if (rc == NGX_OK) {
            return;
        }
    }
}