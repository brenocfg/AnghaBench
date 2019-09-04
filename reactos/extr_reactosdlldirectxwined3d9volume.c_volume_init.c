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
struct wined3d_texture {int dummy; } ;
struct wined3d_parent_ops {int dummy; } ;
struct TYPE_4__ {scalar_t__ refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d9_volume {unsigned int sub_resource_idx; struct wined3d_texture* wined3d_texture; int /*<<< orphan*/  texture; TYPE_2__ resource; TYPE_1__ IDirect3DVolume9_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_resource_init (TYPE_2__*) ; 
 int /*<<< orphan*/  d3d9_volume_vtbl ; 
 struct wined3d_parent_ops d3d9_volume_wined3d_parent_ops ; 
 int /*<<< orphan*/  wined3d_texture_get_parent (struct wined3d_texture*) ; 

void volume_init(struct d3d9_volume *volume, struct wined3d_texture *wined3d_texture,
        unsigned int sub_resource_idx, const struct wined3d_parent_ops **parent_ops)
{
    volume->IDirect3DVolume9_iface.lpVtbl = &d3d9_volume_vtbl;
    d3d9_resource_init(&volume->resource);
    volume->resource.refcount = 0;
    volume->texture = wined3d_texture_get_parent(wined3d_texture);
    volume->wined3d_texture = wined3d_texture;
    volume->sub_resource_idx = sub_resource_idx;

    *parent_ops = &d3d9_volume_wined3d_parent_ops;
}