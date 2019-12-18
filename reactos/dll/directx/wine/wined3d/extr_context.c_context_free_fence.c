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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct wined3d_fence {TYPE_1__ object; struct wined3d_context* context; int /*<<< orphan*/  entry; } ;
struct wined3d_context {scalar_t__ free_fence_count; TYPE_1__* free_fences; int /*<<< orphan*/  free_fence_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,struct wined3d_context*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_array_reserve (void**,int /*<<< orphan*/ *,scalar_t__,int) ; 

void context_free_fence(struct wined3d_fence *fence)
{
    struct wined3d_context *context = fence->context;

    list_remove(&fence->entry);
    fence->context = NULL;

    if (!wined3d_array_reserve((void **)&context->free_fences,
            &context->free_fence_size, context->free_fence_count + 1,
            sizeof(*context->free_fences)))
    {
        ERR("Failed to grow free list, leaking fence %u in context %p.\n", fence->object.id, context);
        return;
    }

    context->free_fences[context->free_fence_count++] = fence->object;
}