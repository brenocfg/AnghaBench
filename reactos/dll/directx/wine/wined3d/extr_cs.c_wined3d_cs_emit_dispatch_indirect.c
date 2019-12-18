#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int dummy; } ;
struct TYPE_6__ {unsigned int offset; struct wined3d_buffer* buffer; } ;
struct TYPE_7__ {TYPE_1__ indirect; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  indirect; } ;
struct wined3d_cs_dispatch {TYPE_3__ parameters; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_4__* ops; TYPE_5__* device; } ;
struct wined3d_buffer {int /*<<< orphan*/  resource; } ;
struct TYPE_10__ {struct wined3d_state state; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_dispatch* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_CS_OP_DISPATCH ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 int /*<<< orphan*/  acquire_compute_pipeline_resources (struct wined3d_state const*) ; 
 struct wined3d_cs_dispatch* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ *) ; 

void wined3d_cs_emit_dispatch_indirect(struct wined3d_cs *cs,
        struct wined3d_buffer *buffer, unsigned int offset)
{
    const struct wined3d_state *state = &cs->device->state;
    struct wined3d_cs_dispatch *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_DISPATCH;
    op->parameters.indirect = TRUE;
    op->parameters.u.indirect.buffer = buffer;
    op->parameters.u.indirect.offset = offset;

    acquire_compute_pipeline_resources(state);
    wined3d_resource_acquire(&buffer->resource);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}