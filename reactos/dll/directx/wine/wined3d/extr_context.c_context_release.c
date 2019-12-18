#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_context {int needs_set; int /*<<< orphan*/  device; scalar_t__ destroy_delayed; int /*<<< orphan*/ * restore_dc; int /*<<< orphan*/ * restore_ctx; int /*<<< orphan*/  gl_info; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*,...) ; 
 int /*<<< orphan*/  WARN (char*,struct wined3d_context*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_destroy (int /*<<< orphan*/ ,struct wined3d_context*) ; 
 struct wined3d_context* context_get_current () ; 
 int /*<<< orphan*/  context_restore_gl_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ context_restore_pixel_format (struct wined3d_context*) ; 
 int /*<<< orphan*/  d3d ; 

void context_release(struct wined3d_context *context)
{
    TRACE("Releasing context %p, level %u.\n", context, context->level);

    if (WARN_ON(d3d))
    {
        if (!context->level)
            WARN("Context %p is not active.\n", context);
        else if (context != context_get_current())
            WARN("Context %p is not the current context.\n", context);
    }

    if (!--context->level)
    {
        if (context_restore_pixel_format(context))
            context->needs_set = 1;
        if (context->restore_ctx)
        {
            TRACE("Restoring GL context %p on device context %p.\n", context->restore_ctx, context->restore_dc);
            context_restore_gl_context(context->gl_info, context->restore_dc, context->restore_ctx);
            context->restore_ctx = NULL;
            context->restore_dc = NULL;
        }

        if (context->destroy_delayed)
        {
            TRACE("Destroying context %p.\n", context);
            context_destroy(context->device, context);
        }
    }
}