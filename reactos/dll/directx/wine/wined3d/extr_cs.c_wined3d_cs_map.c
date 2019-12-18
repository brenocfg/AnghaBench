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
struct wined3d_resource {int dummy; } ;
struct wined3d_map_desc {int dummy; } ;
struct wined3d_cs_map {unsigned int sub_resource_idx; unsigned int flags; int /*<<< orphan*/ * hr; struct wined3d_box const* box; struct wined3d_map_desc* map_desc; struct wined3d_resource* resource; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {TYPE_1__* ops; } ;
struct wined3d_box {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* finish ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_map* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_CS_OP_MAP ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_MAP ; 
 struct wined3d_cs_map* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_not_from_cs (struct wined3d_cs*) ; 

HRESULT wined3d_cs_map(struct wined3d_cs *cs, struct wined3d_resource *resource, unsigned int sub_resource_idx,
        struct wined3d_map_desc *map_desc, const struct wined3d_box *box, unsigned int flags)
{
    struct wined3d_cs_map *op;
    HRESULT hr;

    /* Mapping resources from the worker thread isn't an issue by itself, but
     * increasing the map count would be visible to applications. */
    wined3d_not_from_cs(cs);

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_MAP);
    op->opcode = WINED3D_CS_OP_MAP;
    op->resource = resource;
    op->sub_resource_idx = sub_resource_idx;
    op->map_desc = map_desc;
    op->box = box;
    op->flags = flags;
    op->hr = &hr;

    cs->ops->submit(cs, WINED3D_CS_QUEUE_MAP);
    cs->ops->finish(cs, WINED3D_CS_QUEUE_MAP);

    return hr;
}