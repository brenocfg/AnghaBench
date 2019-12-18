#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_unordered_access_view {TYPE_2__* resource; } ;
struct wined3d_cs_set_unordered_access_view {size_t pipeline; size_t view_idx; unsigned int initial_count; struct wined3d_unordered_access_view* view; } ;
struct TYPE_3__ {struct wined3d_unordered_access_view*** unordered_access_view; } ;
struct wined3d_cs {int /*<<< orphan*/  device; TYPE_1__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  bind_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATE_UNORDERED_ACCESS_VIEW_BINDING (size_t) ; 
 int /*<<< orphan*/  device_invalidate_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_unordered_access_view_set_counter (struct wined3d_unordered_access_view*,unsigned int) ; 

__attribute__((used)) static void wined3d_cs_exec_set_unordered_access_view(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_unordered_access_view *op = data;
    struct wined3d_unordered_access_view *prev;

    prev = cs->state.unordered_access_view[op->pipeline][op->view_idx];
    cs->state.unordered_access_view[op->pipeline][op->view_idx] = op->view;

    if (op->view)
        InterlockedIncrement(&op->view->resource->bind_count);
    if (prev)
        InterlockedDecrement(&prev->resource->bind_count);

    if (op->view && op->initial_count != ~0u)
        wined3d_unordered_access_view_set_counter(op->view, op->initial_count);

    device_invalidate_state(cs->device, STATE_UNORDERED_ACCESS_VIEW_BINDING(op->pipeline));
}