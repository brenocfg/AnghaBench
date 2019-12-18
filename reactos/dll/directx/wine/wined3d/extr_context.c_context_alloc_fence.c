#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {scalar_t__* supported; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * sync; } ;
struct wined3d_fence {int /*<<< orphan*/  entry; struct wined3d_context* context; TYPE_1__ object; } ;
struct wined3d_context {int free_fence_count; int /*<<< orphan*/  fences; TYPE_1__* free_fences; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 size_t APPLE_FENCE ; 
 size_t ARB_SYNC ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 size_t NV_FENCE ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glGenFencesAPPLE (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenFencesNV (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void context_alloc_fence(struct wined3d_context *context, struct wined3d_fence *fence)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (context->free_fence_count)
    {
        fence->object = context->free_fences[--context->free_fence_count];
    }
    else
    {
        if (gl_info->supported[ARB_SYNC])
        {
            /* Using ARB_sync, not much to do here. */
            fence->object.sync = NULL;
            TRACE("Allocated sync object in context %p.\n", context);
        }
        else if (gl_info->supported[APPLE_FENCE])
        {
            GL_EXTCALL(glGenFencesAPPLE(1, &fence->object.id));
            checkGLcall("glGenFencesAPPLE");

            TRACE("Allocated fence %u in context %p.\n", fence->object.id, context);
        }
        else if(gl_info->supported[NV_FENCE])
        {
            GL_EXTCALL(glGenFencesNV(1, &fence->object.id));
            checkGLcall("glGenFencesNV");

            TRACE("Allocated fence %u in context %p.\n", fence->object.id, context);
        }
        else
        {
            WARN("Fences not supported, not allocating fence.\n");
            fence->object.id = 0;
        }
    }

    fence->context = context;
    list_add_head(&context->fences, &fence->entry);
}