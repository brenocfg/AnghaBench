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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; scalar_t__ sync; } ;
struct wined3d_fence {TYPE_2__ object; TYPE_3__* context; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_6__ {TYPE_1__* gl_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * supported; } ;

/* Variables and functions */
 size_t APPLE_FENCE ; 
 size_t ARB_SYNC ; 
 int /*<<< orphan*/  GL_ALL_COMPLETED_NV ; 
 scalar_t__ GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_SYNC_GPU_COMMANDS_COMPLETE ; 
 size_t NV_FENCE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_alloc_fence (struct wined3d_context*,struct wined3d_fence*) ; 
 int /*<<< orphan*/  context_free_fence (struct wined3d_fence*) ; 
 struct wined3d_context* context_reacquire (struct wined3d_device const*,TYPE_3__*) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  glDeleteSync (scalar_t__) ; 
 int /*<<< orphan*/  glFenceSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glSetFenceAPPLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glSetFenceNV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wined3d_fence_issue(struct wined3d_fence *fence, const struct wined3d_device *device)
{
    struct wined3d_context *context = NULL;
    const struct wined3d_gl_info *gl_info;

    if (fence->context && !(context = context_reacquire(device, fence->context))
            && !fence->context->gl_info->supported[ARB_SYNC])
        context_free_fence(fence);
    if (!context)
        context = context_acquire(device, NULL, 0);
    gl_info = context->gl_info;
    if (!fence->context)
        context_alloc_fence(context, fence);

    if (gl_info->supported[ARB_SYNC])
    {
        if (fence->object.sync)
            GL_EXTCALL(glDeleteSync(fence->object.sync));
        checkGLcall("glDeleteSync");
        fence->object.sync = GL_EXTCALL(glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0));
        checkGLcall("glFenceSync");
    }
    else if (gl_info->supported[APPLE_FENCE])
    {
        GL_EXTCALL(glSetFenceAPPLE(fence->object.id));
        checkGLcall("glSetFenceAPPLE");
    }
    else if (gl_info->supported[NV_FENCE])
    {
        GL_EXTCALL(glSetFenceNV(fence->object.id, GL_ALL_COMPLETED_NV));
        checkGLcall("glSetFenceNV");
    }

    context_release(context);
}