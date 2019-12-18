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
struct wined3d_rendertarget_view {int dummy; } ;
struct d3d8_surface {struct wined3d_rendertarget_view* wined3d_rtv; int /*<<< orphan*/  rtv_entry; TYPE_1__* texture; int /*<<< orphan*/  IDirect3DSurface8_iface; int /*<<< orphan*/  sub_resource_idx; int /*<<< orphan*/  wined3d_texture; } ;
struct TYPE_2__ {int /*<<< orphan*/  rtv_list; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_surface_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_surface_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_view_wined3d_parent_ops ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_rendertarget_view_create_from_sub_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3d8_surface*,int /*<<< orphan*/ *,struct wined3d_rendertarget_view**) ; 

struct wined3d_rendertarget_view *d3d8_surface_acquire_rendertarget_view(struct d3d8_surface *surface)
{
    HRESULT hr;

    /* The surface reference count can be equal to 0 when this function is
     * called. In order to properly manage the render target view reference
     * count, we temporarily increment the surface reference count. */
    d3d8_surface_AddRef(&surface->IDirect3DSurface8_iface);

    if (surface->wined3d_rtv)
        return surface->wined3d_rtv;

    if (FAILED(hr = wined3d_rendertarget_view_create_from_sub_resource(surface->wined3d_texture,
            surface->sub_resource_idx, surface, &d3d8_view_wined3d_parent_ops, &surface->wined3d_rtv)))
    {
        ERR("Failed to create rendertarget view, hr %#x.\n", hr);
        d3d8_surface_Release(&surface->IDirect3DSurface8_iface);
        return NULL;
    }

    if (surface->texture)
        list_add_head(&surface->texture->rtv_list, &surface->rtv_entry);

    return surface->wined3d_rtv;
}