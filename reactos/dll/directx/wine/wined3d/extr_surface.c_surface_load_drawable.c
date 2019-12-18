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
struct TYPE_9__ {int usage; struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_4__ resource; TYPE_1__* sub_resources; } ;
struct wined3d_surface {struct wined3d_texture* container; } ;
struct wined3d_device {TYPE_5__* blitter; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_10__ {TYPE_2__* ops; } ;
struct TYPE_8__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* blitter_blit ) (TYPE_5__*,int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  locations; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DUSAGE_DEPTHSTENCIL ; 
 int /*<<< orphan*/  WINED3D_BLIT_OP_COLOR_BLIT ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 int /*<<< orphan*/  WINED3D_TEXF_POINT ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,struct wined3d_texture*,unsigned int) ; 
 struct wined3d_surface* context_get_rt_surface (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_surface*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,struct wined3d_context*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int surface_get_sub_resource_idx (struct wined3d_surface*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_resource_is_offscreen (TYPE_4__*) ; 
 TYPE_3__ wined3d_settings ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL surface_load_drawable(struct wined3d_surface *surface,
        struct wined3d_context *context)
{
    unsigned int sub_resource_idx = surface_get_sub_resource_idx(surface);
    struct wined3d_texture *texture = surface->container;
    struct wined3d_surface *restore_rt = NULL;
    struct wined3d_device *device;
    unsigned int level;
    RECT r;

    if (texture->resource.usage & WINED3DUSAGE_DEPTHSTENCIL)
    {
        DWORD current = texture->sub_resources[sub_resource_idx].locations;
        FIXME("Unimplemented copy from %s for depth/stencil buffers.\n",
                wined3d_debug_location(current));
        return FALSE;
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO
            && wined3d_resource_is_offscreen(&texture->resource))
    {
        ERR("Trying to load offscreen surface into WINED3D_LOCATION_DRAWABLE.\n");
        return FALSE;
    }

    device = texture->resource.device;
    restore_rt = context_get_rt_surface(context);
    if (restore_rt != surface)
        context = context_acquire(device, texture, sub_resource_idx);
    else
        restore_rt = NULL;

    level = sub_resource_idx % texture->level_count;
    SetRect(&r, 0, 0, wined3d_texture_get_level_width(texture, level),
            wined3d_texture_get_level_height(texture, level));
    wined3d_texture_load_location(texture, sub_resource_idx, context, WINED3D_LOCATION_TEXTURE_RGB);
    device->blitter->ops->blitter_blit(device->blitter, WINED3D_BLIT_OP_COLOR_BLIT, context,
            surface, WINED3D_LOCATION_TEXTURE_RGB, &r,
            surface, WINED3D_LOCATION_DRAWABLE, &r,
            NULL, WINED3D_TEXF_POINT);

    if (restore_rt)
        context_restore(context, restore_rt);

    return TRUE;
}