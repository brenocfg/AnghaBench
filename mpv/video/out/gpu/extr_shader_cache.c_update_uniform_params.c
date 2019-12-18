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
struct ra_layout {size_t size; int /*<<< orphan*/  align; } ;
struct TYPE_7__ {int dim_m; } ;
struct sc_uniform {size_t offset; int /*<<< orphan*/  type; struct ra_layout layout; TYPE_3__ input; } ;
struct gl_shader_cache {int next_uniform_dynamic; size_t pushc_size; size_t ubo_size; TYPE_2__* ra; } ;
struct TYPE_6__ {size_t max_pushc_size; int caps; int glsl_version; TYPE_1__* fns; scalar_t__ glsl_vulkan; } ;
struct TYPE_5__ {struct ra_layout (* uniform_layout ) (TYPE_3__*) ;struct ra_layout (* push_constant_layout ) (TYPE_3__*) ;} ;

/* Variables and functions */
 void* MP_ALIGN_UP (size_t,int /*<<< orphan*/ ) ; 
 int RA_CAP_BUF_RO ; 
 int RA_CAP_GLOBAL_UNIFORM ; 
 int /*<<< orphan*/  SC_UNIFORM_TYPE_GLOBAL ; 
 int /*<<< orphan*/  SC_UNIFORM_TYPE_PUSHC ; 
 int /*<<< orphan*/  SC_UNIFORM_TYPE_UBO ; 
 int /*<<< orphan*/  assert (int) ; 
 struct ra_layout stub1 (TYPE_3__*) ; 
 struct ra_layout stub2 (TYPE_3__*) ; 

__attribute__((used)) static void update_uniform_params(struct gl_shader_cache *sc, struct sc_uniform *u)
{
    bool dynamic = sc->next_uniform_dynamic;
    sc->next_uniform_dynamic = false;

    // Try not using push constants for "large" values like matrices, since
    // this is likely to both exceed the VGPR budget as well as the pushc size
    // budget
    bool try_pushc = u->input.dim_m == 1 || dynamic;

    // Attempt using push constants first
    if (try_pushc && sc->ra->glsl_vulkan && sc->ra->max_pushc_size) {
        struct ra_layout layout = sc->ra->fns->push_constant_layout(&u->input);
        size_t offset = MP_ALIGN_UP(sc->pushc_size, layout.align);
        // Push constants have limited size, so make sure we don't exceed this
        size_t new_size = offset + layout.size;
        if (new_size <= sc->ra->max_pushc_size) {
            u->type = SC_UNIFORM_TYPE_PUSHC;
            u->layout = layout;
            u->offset = offset;
            sc->pushc_size = new_size;
            return;
        }
    }

    // Attempt using uniform buffer next. The GLSL version 440 check is due
    // to explicit offsets on UBO entries. In theory we could leave away
    // the offsets and support UBOs for older GL as well, but this is a nice
    // safety net for driver bugs (and also rules out potentially buggy drivers)
    // Also avoid UBOs for highly dynamic stuff since that requires synchronizing
    // the UBO writes every frame
    bool try_ubo = !(sc->ra->caps & RA_CAP_GLOBAL_UNIFORM) || !dynamic;
    if (try_ubo && sc->ra->glsl_version >= 440 && (sc->ra->caps & RA_CAP_BUF_RO)) {
        u->type = SC_UNIFORM_TYPE_UBO;
        u->layout = sc->ra->fns->uniform_layout(&u->input);
        u->offset = MP_ALIGN_UP(sc->ubo_size, u->layout.align);
        sc->ubo_size = u->offset + u->layout.size;
        return;
    }

    // If all else fails, use global uniforms
    assert(sc->ra->caps & RA_CAP_GLOBAL_UNIFORM);
    u->type = SC_UNIFORM_TYPE_GLOBAL;
}