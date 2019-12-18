#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_surface {TYPE_1__* container; } ;
struct wined3d_resource {int format_flags; TYPE_2__* format; struct wined3d_device* device; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int /*<<< orphan*/  gl_info; } ;
struct wined3d_color_key {int dummy; } ;
struct wined3d_blitter {TYPE_3__* ops; struct wined3d_blitter* next; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
struct TYPE_6__ {int /*<<< orphan*/  (* blitter_blit ) (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ;} ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_4__ {struct wined3d_resource resource; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3D_BLIT_OP_COLOR_BLIT ; 
 int WINED3D_BLIT_OP_DEPTH_BLIT ; 
 int WINED3D_BLIT_OP_RAW_BLIT ; 
 int /*<<< orphan*/  fbo_blitter_supported (int,int /*<<< orphan*/ ,struct wined3d_resource*,int /*<<< orphan*/ ,struct wined3d_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ; 
 int /*<<< orphan*/  surface_blt_fbo (struct wined3d_device*,struct wined3d_context*,int,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  surface_depth_blt_fbo (struct wined3d_device*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static DWORD fbo_blitter_blit(struct wined3d_blitter *blitter, enum wined3d_blit_op op,
        struct wined3d_context *context, struct wined3d_surface *src_surface, DWORD src_location,
        const RECT *src_rect, struct wined3d_surface *dst_surface, DWORD dst_location, const RECT *dst_rect,
        const struct wined3d_color_key *colour_key, enum wined3d_texture_filter_type filter)
{
    struct wined3d_resource *src_resource = &src_surface->container->resource;
    struct wined3d_resource *dst_resource = &dst_surface->container->resource;
    struct wined3d_device *device = dst_resource->device;
    enum wined3d_blit_op blit_op = op;
    struct wined3d_blitter *next;

    if (blit_op == WINED3D_BLIT_OP_RAW_BLIT && dst_resource->format->id == src_resource->format->id)
    {
        if (dst_resource->format_flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
            blit_op = WINED3D_BLIT_OP_DEPTH_BLIT;
        else
            blit_op = WINED3D_BLIT_OP_COLOR_BLIT;
    }

    if (!fbo_blitter_supported(blit_op, context->gl_info,
            src_resource, src_location, dst_resource, dst_location))
    {
        if ((next = blitter->next))
            return next->ops->blitter_blit(next, op, context, src_surface, src_location,
                    src_rect, dst_surface, dst_location, dst_rect, colour_key, filter);
    }

    if (blit_op == WINED3D_BLIT_OP_COLOR_BLIT)
    {
        TRACE("Colour blit.\n");
        surface_blt_fbo(device, context, filter, src_surface, src_location,
                src_rect, dst_surface, dst_location, dst_rect);
        return dst_location;
    }

    if (blit_op == WINED3D_BLIT_OP_DEPTH_BLIT)
    {
        TRACE("Depth/stencil blit.\n");
        surface_depth_blt_fbo(device, src_surface, src_location, src_rect, dst_surface, dst_location, dst_rect);
        return dst_location;
    }

    ERR("This blitter does not implement blit op %#x.\n", blit_op);
    return dst_location;
}