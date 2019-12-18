#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
struct TYPE_9__ {int base_vertex_idx; unsigned int start_idx; unsigned int index_count; unsigned int start_instance; unsigned int instance_count; } ;
struct TYPE_10__ {TYPE_3__ direct; } ;
struct TYPE_11__ {int /*<<< orphan*/  indexed; TYPE_4__ u; int /*<<< orphan*/  indirect; } ;
struct wined3d_cs_draw {unsigned int patch_vertex_count; TYPE_5__ parameters; int /*<<< orphan*/  primitive_type; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_6__* ops; TYPE_2__* device; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_draw* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {struct wined3d_state state; TYPE_1__* adapter; } ;
struct TYPE_7__ {struct wined3d_gl_info gl_info; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WINED3D_CS_OP_DRAW ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 int /*<<< orphan*/  acquire_graphics_pipeline_resources (struct wined3d_state const*,int /*<<< orphan*/ ,struct wined3d_gl_info const*) ; 
 struct wined3d_cs_draw* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_draw(struct wined3d_cs *cs, GLenum primitive_type, unsigned int patch_vertex_count,
        int base_vertex_idx, unsigned int start_idx, unsigned int index_count,
        unsigned int start_instance, unsigned int instance_count, BOOL indexed)
{
    const struct wined3d_gl_info *gl_info = &cs->device->adapter->gl_info;
    const struct wined3d_state *state = &cs->device->state;
    struct wined3d_cs_draw *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_DRAW;
    op->primitive_type = primitive_type;
    op->patch_vertex_count = patch_vertex_count;
    op->parameters.indirect = FALSE;
    op->parameters.u.direct.base_vertex_idx = base_vertex_idx;
    op->parameters.u.direct.start_idx = start_idx;
    op->parameters.u.direct.index_count = index_count;
    op->parameters.u.direct.start_instance = start_instance;
    op->parameters.u.direct.instance_count = instance_count;
    op->parameters.indexed = indexed;

    acquire_graphics_pipeline_resources(state, indexed, gl_info);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}