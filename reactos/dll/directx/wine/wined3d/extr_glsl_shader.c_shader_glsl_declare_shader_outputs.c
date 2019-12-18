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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
typedef  enum wined3d_shader_interpolation_mode { ____Placeholder_wined3d_shader_interpolation_mode } wined3d_shader_interpolation_mode ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  declare_out_varying (struct wined3d_gl_info const*,struct wined3d_string_buffer*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ needs_interpolation_qualifiers_for_shader_outputs (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 char* shader_glsl_interpolation_qualifiers (int) ; 
 scalar_t__ shader_glsl_use_interface_blocks (struct wined3d_gl_info const*) ; 
 int wined3d_extract_interpolation_mode (int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void shader_glsl_declare_shader_outputs(const struct wined3d_gl_info *gl_info,
        struct wined3d_string_buffer *buffer, unsigned int element_count, BOOL rasterizer_setup,
        const DWORD *interpolation_mode)
{
    enum wined3d_shader_interpolation_mode mode;
    unsigned int i;

    if (shader_glsl_use_interface_blocks(gl_info))
    {
        if (rasterizer_setup)
        {
            shader_addline(buffer, "out shader_in_out {\n");
            for (i = 0; i < element_count; ++i)
            {
                const char *interpolation_qualifiers = "";
                if (needs_interpolation_qualifiers_for_shader_outputs(gl_info))
                {
                    mode = wined3d_extract_interpolation_mode(interpolation_mode, i);
                    interpolation_qualifiers = shader_glsl_interpolation_qualifiers(mode);
                }
                shader_addline(buffer, "%s vec4 reg%u;\n", interpolation_qualifiers, i);
            }
            shader_addline(buffer, "} shader_out;\n");
        }
        else
        {
            shader_addline(buffer, "out shader_in_out { vec4 reg[%u]; } shader_out;\n", element_count);
        }
    }
    else
    {
        declare_out_varying(gl_info, buffer, FALSE, "vec4 ps_link[%u];\n", element_count);
    }
}