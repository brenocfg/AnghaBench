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
struct wined3d_shader_resource_info {int /*<<< orphan*/  type; } ;
struct wined3d_context {size_t* rev_tex_unit_map; unsigned int fixed_function_usage_map; } ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t MAX_FRAGMENT_SAMPLERS ; 
 size_t MAX_TEXTURES ; 
 int TRUE ; 
 size_t WINED3D_UNMAPPED_STAGE ; 

__attribute__((used)) static BOOL context_unit_free_for_vs(const struct wined3d_context *context,
        const struct wined3d_shader_resource_info *ps_resource_info, DWORD unit)
{
    DWORD current_mapping = context->rev_tex_unit_map[unit];

    /* Not currently used */
    if (current_mapping == WINED3D_UNMAPPED_STAGE)
        return TRUE;

    if (current_mapping < MAX_FRAGMENT_SAMPLERS)
    {
        /* Used by a fragment sampler */

        if (!ps_resource_info)
        {
            /* No pixel shader, check fixed function */
            return current_mapping >= MAX_TEXTURES || !(context->fixed_function_usage_map & (1u << current_mapping));
        }

        /* Pixel shader, check the shader's sampler map */
        return !ps_resource_info[current_mapping].type;
    }

    return TRUE;
}