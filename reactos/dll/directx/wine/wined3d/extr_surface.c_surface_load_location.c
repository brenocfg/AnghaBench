#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_surface {int dummy; } ;
struct wined3d_context {int dummy; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_surface*,int /*<<< orphan*/ ) ; 
#define  WINED3D_LOCATION_BUFFER 135 
#define  WINED3D_LOCATION_DRAWABLE 134 
#define  WINED3D_LOCATION_RB_MULTISAMPLE 133 
#define  WINED3D_LOCATION_RB_RESOLVED 132 
#define  WINED3D_LOCATION_SYSMEM 131 
#define  WINED3D_LOCATION_TEXTURE_RGB 130 
#define  WINED3D_LOCATION_TEXTURE_SRGB 129 
#define  WINED3D_LOCATION_USER_MEMORY 128 
 int /*<<< orphan*/  surface_load_drawable (struct wined3d_surface*,struct wined3d_context*) ; 
 int /*<<< orphan*/  surface_load_renderbuffer (struct wined3d_surface*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  surface_load_sysmem (struct wined3d_surface*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  surface_load_texture (struct wined3d_surface*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 

BOOL surface_load_location(struct wined3d_surface *surface, struct wined3d_context *context, DWORD location)
{
    TRACE("surface %p, location %s.\n", surface, wined3d_debug_location(location));

    switch (location)
    {
        case WINED3D_LOCATION_USER_MEMORY:
        case WINED3D_LOCATION_SYSMEM:
        case WINED3D_LOCATION_BUFFER:
            return surface_load_sysmem(surface, context, location);

        case WINED3D_LOCATION_DRAWABLE:
            return surface_load_drawable(surface, context);

        case WINED3D_LOCATION_RB_RESOLVED:
        case WINED3D_LOCATION_RB_MULTISAMPLE:
            return surface_load_renderbuffer(surface, context, location);

        case WINED3D_LOCATION_TEXTURE_RGB:
        case WINED3D_LOCATION_TEXTURE_SRGB:
            return surface_load_texture(surface, context,
                    location == WINED3D_LOCATION_TEXTURE_SRGB);

        default:
            ERR("Don't know how to handle location %#x.\n", location);
            return FALSE;
    }
}