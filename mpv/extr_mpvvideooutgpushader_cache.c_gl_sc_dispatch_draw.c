#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timer_pool {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; } ;
struct ra_tex {TYPE_2__ params; } ;
struct mp_rect {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ra_renderpass_run_params {void* vertex_data; size_t vertex_count; struct mp_rect scissors; struct mp_rect viewport; struct ra_tex* target; int /*<<< orphan*/  push_constants; int /*<<< orphan*/  num_values; int /*<<< orphan*/  values; int /*<<< orphan*/  pass; } ;
struct ra_renderpass_input {int dummy; } ;
struct mp_pass_perf {int dummy; } ;
struct TYPE_6__ {int invalidate_target; } ;
struct gl_shader_cache {TYPE_5__* ra; TYPE_3__* current_shader; int /*<<< orphan*/  num_values; int /*<<< orphan*/  values; TYPE_1__ params; } ;
struct TYPE_10__ {TYPE_4__* fns; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* renderpass_run ) (TYPE_5__*,struct ra_renderpass_run_params*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  pushc; int /*<<< orphan*/  pass; struct timer_pool* timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_RENDERPASS_TYPE_RASTER ; 
 int /*<<< orphan*/  gl_sc_generate (struct gl_shader_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_renderpass_input const*,int,size_t) ; 
 int /*<<< orphan*/  gl_sc_reset (struct gl_shader_cache*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct ra_renderpass_run_params*) ; 
 struct mp_pass_perf timer_pool_measure (struct timer_pool*) ; 
 int /*<<< orphan*/  timer_pool_start (struct timer_pool*) ; 
 int /*<<< orphan*/  timer_pool_stop (struct timer_pool*) ; 

struct mp_pass_perf gl_sc_dispatch_draw(struct gl_shader_cache *sc,
                                        struct ra_tex *target, bool discard,
                                        const struct ra_renderpass_input *vao,
                                        int vao_len, size_t vertex_stride,
                                        void *vertices, size_t num_vertices)
{
    struct timer_pool *timer = NULL;

    sc->params.invalidate_target = discard;
    gl_sc_generate(sc, RA_RENDERPASS_TYPE_RASTER, target->params.format,
                   vao, vao_len, vertex_stride);
    if (!sc->current_shader)
        goto error;

    timer = sc->current_shader->timer;

    struct mp_rect full_rc = {0, 0, target->params.w, target->params.h};

    struct ra_renderpass_run_params run = {
        .pass = sc->current_shader->pass,
        .values = sc->values,
        .num_values = sc->num_values,
        .push_constants = sc->current_shader->pushc,
        .target = target,
        .vertex_data = vertices,
        .vertex_count = num_vertices,
        .viewport = full_rc,
        .scissors = full_rc,
    };

    timer_pool_start(timer);
    sc->ra->fns->renderpass_run(sc->ra, &run);
    timer_pool_stop(timer);

error:
    gl_sc_reset(sc);
    return timer_pool_measure(timer);
}