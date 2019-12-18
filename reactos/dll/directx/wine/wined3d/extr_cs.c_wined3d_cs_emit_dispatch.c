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
struct TYPE_7__ {unsigned int group_count_x; unsigned int group_count_y; unsigned int group_count_z; } ;
struct TYPE_8__ {TYPE_2__ direct; } ;
struct TYPE_9__ {TYPE_3__ u; int /*<<< orphan*/  indirect; } ;
struct wined3d_cs_dispatch {TYPE_4__ parameters; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_5__* ops; TYPE_1__* device; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_dispatch* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct wined3d_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WINED3D_CS_OP_DISPATCH ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 int /*<<< orphan*/  acquire_compute_pipeline_resources (struct wined3d_state const*) ; 
 struct wined3d_cs_dispatch* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 

void wined3d_cs_emit_dispatch(struct wined3d_cs *cs,
        unsigned int group_count_x, unsigned int group_count_y, unsigned int group_count_z)
{
    const struct wined3d_state *state = &cs->device->state;
    struct wined3d_cs_dispatch *op;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_DISPATCH;
    op->parameters.indirect = FALSE;
    op->parameters.u.direct.group_count_x = group_count_x;
    op->parameters.u.direct.group_count_y = group_count_y;
    op->parameters.u.direct.group_count_z = group_count_z;

    acquire_compute_pipeline_resources(state);

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);
}