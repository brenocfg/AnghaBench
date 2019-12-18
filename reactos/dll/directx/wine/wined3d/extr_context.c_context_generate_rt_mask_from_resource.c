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
struct wined3d_resource {scalar_t__ type; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_2D ; 
 int /*<<< orphan*/  debug_d3dresourcetype (scalar_t__) ; 
 int /*<<< orphan*/  texture_from_resource (struct wined3d_resource*) ; 
 unsigned int wined3d_texture_get_gl_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DWORD context_generate_rt_mask_from_resource(struct wined3d_resource *resource)
{
    if (resource->type != WINED3D_RTYPE_TEXTURE_2D)
    {
        FIXME("Not implemented for %s resources.\n", debug_d3dresourcetype(resource->type));
        return 0;
    }

    return (1u << 31) | wined3d_texture_get_gl_buffer(texture_from_resource(resource));
}