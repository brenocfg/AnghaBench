#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  log; TYPE_3__* data; } ;
struct TYPE_14__ {TYPE_10__ respawn_evt; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_rtmp_exec_t ;
struct TYPE_13__ {scalar_t__ nelts; TYPE_3__* elts; } ;
struct TYPE_15__ {TYPE_2__ static_exec; } ;
typedef  TYPE_4__ ngx_rtmp_exec_main_conf_t ;
struct TYPE_16__ {TYPE_7__* ctx; } ;
typedef  TYPE_5__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_12__ {scalar_t__ nelts; TYPE_5__** elts; } ;
struct TYPE_17__ {TYPE_1__ servers; } ;
typedef  TYPE_6__ ngx_rtmp_core_main_conf_t ;
struct TYPE_18__ {TYPE_4__** main_conf; } ;
typedef  TYPE_7__ ngx_rtmp_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_19__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_10__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_process_slot ; 
 TYPE_6__* ngx_rtmp_core_main_conf ; 
 TYPE_8__ ngx_rtmp_exec_module ; 
 int /*<<< orphan*/  ngx_rtmp_exec_respawn ; 
 int /*<<< orphan*/  ngx_rtmp_init_queue ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_init_process(ngx_cycle_t *cycle)
{
#if !(NGX_WIN32)
    ngx_rtmp_core_main_conf_t  *cmcf = ngx_rtmp_core_main_conf;
    ngx_rtmp_core_srv_conf_t  **cscf;
    ngx_rtmp_conf_ctx_t        *cctx;
    ngx_rtmp_exec_main_conf_t  *emcf;
    ngx_rtmp_exec_t            *e;
    ngx_uint_t                  n;

    if (cmcf == NULL || cmcf->servers.nelts == 0) {
        return NGX_OK;
    }

    /* execs are always started by the first worker */
    if (ngx_process_slot) {
        return NGX_OK;
    }

    cscf = cmcf->servers.elts;
    cctx = (*cscf)->ctx;
    emcf = cctx->main_conf[ngx_rtmp_exec_module.ctx_index];

    /* FreeBSD note:
     * When worker is restarted, child process (ffmpeg) will
     * not be terminated if it's connected to another
     * (still alive) worker. That leads to starting
     * another instance of exec_static process.
     * Need to kill previously started processes.
     *
     * On Linux "prctl" syscall is used to kill child
     * when nginx worker is terminated.
     */

    e = emcf->static_exec.elts;
    for (n = 0; n < emcf->static_exec.nelts; ++n, ++e) {
        e->respawn_evt.data = e;
        e->respawn_evt.log = e->log;
        e->respawn_evt.handler = ngx_rtmp_exec_respawn;
        ngx_post_event((&e->respawn_evt), &ngx_rtmp_init_queue);
    }
#endif

    return NGX_OK;
}