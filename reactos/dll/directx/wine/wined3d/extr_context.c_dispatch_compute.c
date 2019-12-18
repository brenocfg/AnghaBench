#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int /*<<< orphan*/ * shader; } ;
struct wined3d_indirect_dispatch_parameters {scalar_t__ offset; struct wined3d_buffer* buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_glFlush ) () ;} ;
struct TYPE_7__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; int /*<<< orphan*/ * supported; } ;
struct wined3d_direct_dispatch_parameters {int /*<<< orphan*/  group_count_z; int /*<<< orphan*/  group_count_y; int /*<<< orphan*/  group_count_x; } ;
struct TYPE_5__ {struct wined3d_direct_dispatch_parameters direct; struct wined3d_indirect_dispatch_parameters indirect; } ;
struct wined3d_dispatch_parameters {TYPE_1__ u; scalar_t__ indirect; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; int /*<<< orphan*/  valid; } ;
struct wined3d_buffer {int /*<<< orphan*/  buffer_object; } ;
struct TYPE_8__ {scalar_t__ strict_draw_ordering; } ;
typedef  int /*<<< orphan*/  GLintptr ;

/* Variables and functions */
 size_t ARB_COMPUTE_SHADER ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_ALL_BARRIER_BITS ; 
 int /*<<< orphan*/  GL_DISPATCH_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 size_t WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_apply_compute_state (struct wined3d_context*,struct wined3d_device*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDispatchCompute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDispatchComputeIndirect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMemoryBarrier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  wined3d_buffer_load (struct wined3d_buffer*,struct wined3d_context*,struct wined3d_state const*) ; 
 TYPE_4__ wined3d_settings ; 

void dispatch_compute(struct wined3d_device *device, const struct wined3d_state *state,
        const struct wined3d_dispatch_parameters *parameters)
{
    const struct wined3d_gl_info *gl_info;
    struct wined3d_context *context;

    context = context_acquire(device, NULL, 0);
    if (!context->valid)
    {
        context_release(context);
        WARN("Invalid context, skipping dispatch.\n");
        return;
    }
    gl_info = context->gl_info;

    if (!gl_info->supported[ARB_COMPUTE_SHADER])
    {
        context_release(context);
        FIXME("OpenGL implementation does not support compute shaders.\n");
        return;
    }

    if (parameters->indirect)
        wined3d_buffer_load(parameters->u.indirect.buffer, context, state);

    context_apply_compute_state(context, device, state);

    if (!state->shader[WINED3D_SHADER_TYPE_COMPUTE])
    {
        context_release(context);
        WARN("No compute shader bound, skipping dispatch.\n");
        return;
    }

    if (parameters->indirect)
    {
        const struct wined3d_indirect_dispatch_parameters *indirect = &parameters->u.indirect;
        struct wined3d_buffer *buffer = indirect->buffer;

        GL_EXTCALL(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, buffer->buffer_object));
        GL_EXTCALL(glDispatchComputeIndirect((GLintptr)indirect->offset));
        GL_EXTCALL(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0));
    }
    else
    {
        const struct wined3d_direct_dispatch_parameters *direct = &parameters->u.direct;
        GL_EXTCALL(glDispatchCompute(direct->group_count_x, direct->group_count_y, direct->group_count_z));
    }
    checkGLcall("dispatch compute");

    GL_EXTCALL(glMemoryBarrier(GL_ALL_BARRIER_BITS));
    checkGLcall("glMemoryBarrier");

    if (wined3d_settings.strict_draw_ordering)
        gl_info->gl_ops.gl.p_glFlush(); /* Flush to ensure ordering across contexts. */

    context_release(context);
}