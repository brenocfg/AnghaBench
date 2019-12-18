#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wined3d_surface {TYPE_9__* container; } ;
struct wined3d_rendertarget_view {TYPE_6__* format; int /*<<< orphan*/  sub_resource_idx; } ;
struct wined3d_device {TYPE_4__** swapchains; } ;
struct wined3d_cs_set_depth_stencil_view {TYPE_8__* view; } ;
struct TYPE_14__ {TYPE_8__* depth_stencil; } ;
struct TYPE_11__ {TYPE_1__* fb; } ;
struct wined3d_cs {TYPE_5__ fb; TYPE_2__ state; struct wined3d_device* device; } ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {TYPE_7__* format; } ;
struct TYPE_16__ {scalar_t__ depth_bias_scale; } ;
struct TYPE_15__ {scalar_t__ depth_bias_scale; } ;
struct TYPE_12__ {int flags; } ;
struct TYPE_13__ {TYPE_3__ desc; } ;
struct TYPE_10__ {struct wined3d_rendertarget_view* depth_stencil; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DISCARDED ; 
 int /*<<< orphan*/  WINED3D_RS_DEPTHBIAS ; 
 int /*<<< orphan*/  WINED3D_RS_DEPTHBIASCLAMP ; 
 int /*<<< orphan*/  WINED3D_RS_STENCILENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_STENCILWRITEMASK ; 
 int /*<<< orphan*/  WINED3D_RS_ZENABLE ; 
 int WINED3D_SWAPCHAIN_DISCARD_DEPTHSTENCIL ; 
 int WINED3D_TEXTURE_DISCARD ; 
 int /*<<< orphan*/  device_invalidate_state (struct wined3d_device*,int /*<<< orphan*/ ) ; 
 struct wined3d_surface* wined3d_rendertarget_view_get_surface (struct wined3d_rendertarget_view*) ; 
 int /*<<< orphan*/  wined3d_texture_validate_location (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_set_depth_stencil_view(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_depth_stencil_view *op = data;
    struct wined3d_device *device = cs->device;
    struct wined3d_rendertarget_view *prev;

    if ((prev = cs->state.fb->depth_stencil))
    {
        struct wined3d_surface *prev_surface = wined3d_rendertarget_view_get_surface(prev);

        if (prev_surface && (device->swapchains[0]->desc.flags & WINED3D_SWAPCHAIN_DISCARD_DEPTHSTENCIL
                || prev_surface->container->flags & WINED3D_TEXTURE_DISCARD))
        {
            wined3d_texture_validate_location(prev_surface->container,
                    prev->sub_resource_idx, WINED3D_LOCATION_DISCARDED);
        }
    }

    cs->fb.depth_stencil = op->view;

    if (!prev != !op->view)
    {
        /* Swapping NULL / non NULL depth stencil affects the depth and tests */
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_ZENABLE));
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_STENCILENABLE));
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_STENCILWRITEMASK));
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_DEPTHBIAS));
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_DEPTHBIASCLAMP));
    }
    else if (prev && prev->format->depth_bias_scale != op->view->format->depth_bias_scale)
    {
        device_invalidate_state(device, STATE_RENDER(WINED3D_RS_DEPTHBIAS));
    }

    device_invalidate_state(device, STATE_FRAMEBUFFER);
}