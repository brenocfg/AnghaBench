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
struct wined3d_shader_version {int major; int /*<<< orphan*/  type; } ;
struct wined3d_gl_info {int /*<<< orphan*/  limits; } ;
struct wined3d_context {int /*<<< orphan*/  const* tex_unit_map; struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 unsigned int MAX_FRAGMENT_SAMPLERS ; 
 unsigned int MAX_TEXTURES ; 
 unsigned int MAX_VERTEX_SAMPLERS ; 
#define  WINED3D_SHADER_TYPE_PIXEL 129 
#define  WINED3D_SHADER_TYPE_VERTEX 128 
 int /*<<< orphan*/  wined3d_gl_limits_get_texture_unit_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

const DWORD *context_get_tex_unit_mapping(const struct wined3d_context *context,
        const struct wined3d_shader_version *shader_version, unsigned int *base, unsigned int *count)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (!shader_version)
    {
        *base = 0;
        *count = MAX_TEXTURES;
        return context->tex_unit_map;
    }

    if (shader_version->major >= 4)
    {
        wined3d_gl_limits_get_texture_unit_range(&gl_info->limits, shader_version->type, base, count);
        return NULL;
    }

    switch (shader_version->type)
    {
        case WINED3D_SHADER_TYPE_PIXEL:
            *base = 0;
            *count = MAX_FRAGMENT_SAMPLERS;
            break;
        case WINED3D_SHADER_TYPE_VERTEX:
            *base = MAX_FRAGMENT_SAMPLERS;
            *count = MAX_VERTEX_SAMPLERS;
            break;
        default:
            ERR("Unhandled shader type %#x.\n", shader_version->type);
            *base = 0;
            *count = 0;
    }

    return context->tex_unit_map;
}