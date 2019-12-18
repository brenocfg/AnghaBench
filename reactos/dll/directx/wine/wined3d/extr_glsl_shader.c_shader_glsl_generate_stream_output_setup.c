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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_stream_output_element {unsigned int component_idx; int component_count; int /*<<< orphan*/  register_idx; scalar_t__ stream_idx; } ;
struct wined3d_stream_output_desc {unsigned int element_count; struct wined3d_stream_output_element* elements; } ;
struct wined3d_shader {TYPE_1__* limits; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  packed_output; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  WINED3D_STREAM_OUTPUT_GAP ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (unsigned int,char*) ; 

__attribute__((used)) static void shader_glsl_generate_stream_output_setup(struct shader_glsl_priv *priv,
        const struct wined3d_shader *shader, const struct wined3d_stream_output_desc *so_desc)
{
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    unsigned int i;

    shader_addline(buffer, "out shader_in_out\n{\n");
    for (i = 0; i < so_desc->element_count; ++i)
    {
        const struct wined3d_stream_output_element *e = &so_desc->elements[i];

        if (e->stream_idx)
        {
            FIXME("Unhandled stream %u.\n", e->stream_idx);
            continue;
        }
        if (e->register_idx == WINED3D_STREAM_OUTPUT_GAP)
            continue;

        if (e->component_idx || e->component_count != 4)
        {
            if (e->component_count == 1)
                shader_addline(buffer, "float");
            else
                shader_addline(buffer, "vec%u", e->component_count);
            shader_addline(buffer, " reg%u_%u_%u;\n",
                    e->register_idx, e->component_idx, e->component_idx + e->component_count - 1);
        }
        else
        {
            shader_addline(buffer, "vec4 reg%u;\n", e->register_idx);
        }
    }
    shader_addline(buffer, "} shader_out;\n");

    shader_addline(buffer, "void setup_gs_output(in vec4 outputs[%u])\n{\n",
            shader->limits->packed_output);
    for (i = 0; i < so_desc->element_count; ++i)
    {
        const struct wined3d_stream_output_element *e = &so_desc->elements[i];

        if (e->stream_idx)
        {
            FIXME("Unhandled stream %u.\n", e->stream_idx);
            continue;
        }
        if (e->register_idx == WINED3D_STREAM_OUTPUT_GAP)
            continue;

        if (e->component_idx || e->component_count != 4)
        {
            DWORD write_mask;
            char str_mask[6];

            write_mask = ((1u << e->component_count) - 1) << e->component_idx;
            shader_glsl_write_mask_to_str(write_mask, str_mask);
            shader_addline(buffer, "shader_out.reg%u_%u_%u = outputs[%u]%s;\n",
                    e->register_idx, e->component_idx, e->component_idx + e->component_count - 1,
                    e->register_idx, str_mask);
        }
        else
        {
            shader_addline(buffer, "shader_out.reg%u = outputs[%u];\n",
                    e->register_idx, e->register_idx);
        }
    }
    shader_addline(buffer, "}\n");
}