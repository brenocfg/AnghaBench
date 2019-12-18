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
struct wined3d_unordered_access_view {int /*<<< orphan*/ * resource; } ;
struct wined3d_cs_copy_uav_counter {TYPE_1__* buffer; int /*<<< orphan*/  offset; struct wined3d_unordered_access_view* view; } ;
struct wined3d_cs {int /*<<< orphan*/  device; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  wined3d_resource_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_unordered_access_view_copy_counter (struct wined3d_unordered_access_view*,TYPE_1__*,int /*<<< orphan*/ ,struct wined3d_context*) ; 

__attribute__((used)) static void wined3d_cs_exec_copy_uav_counter(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_copy_uav_counter *op = data;
    struct wined3d_unordered_access_view *view = op->view;
    struct wined3d_context *context;

    context = context_acquire(cs->device, NULL, 0);
    wined3d_unordered_access_view_copy_counter(view, op->buffer, op->offset, context);
    context_release(context);

    wined3d_resource_release(&op->buffer->resource);
    wined3d_resource_release(view->resource);
}