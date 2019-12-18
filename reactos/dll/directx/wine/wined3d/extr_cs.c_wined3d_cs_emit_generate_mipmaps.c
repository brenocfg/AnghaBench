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
struct wined3d_shader_resource_view {int /*<<< orphan*/  resource; } ;
struct wined3d_cs_generate_mipmaps {struct wined3d_shader_resource_view* view; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_generate_mipmaps* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_GENERATE_MIPMAPS ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_generate_mipmaps* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_generate_mipmaps(struct wined3d_cs *cs, struct wined3d_shader_resource_view *view)
{
    struct wined3d_cs_generate_mipmaps *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_GENERATE_MIPMAPS;
    op->view = view;

    wined3d_resource_acquire(view->resource);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}