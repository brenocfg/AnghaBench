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
struct wined3d_uvec4 {int dummy; } ;
struct wined3d_unordered_access_view {int /*<<< orphan*/  resource; } ;
struct wined3d_cs_clear_unordered_access_view {struct wined3d_uvec4 clear_value; struct wined3d_unordered_access_view* view; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_clear_unordered_access_view* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_CLEAR_UNORDERED_ACCESS_VIEW ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_clear_unordered_access_view* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_clear_unordered_access_view_uint(struct wined3d_cs *cs,
        struct wined3d_unordered_access_view *view, const struct wined3d_uvec4 *clear_value)
{
    struct wined3d_cs_clear_unordered_access_view *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_CLEAR_UNORDERED_ACCESS_VIEW;
    op->view = view;
    op->clear_value = *clear_value;

    wined3d_resource_acquire(view->resource);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}