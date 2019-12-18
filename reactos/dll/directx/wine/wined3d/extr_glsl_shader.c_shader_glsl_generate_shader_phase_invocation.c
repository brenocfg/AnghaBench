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
struct wined3d_shader_phase {scalar_t__ instance_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_glsl_generate_shader_phase_invocation(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_phase *phase, const char *phase_name, unsigned int phase_idx)
{
    if (phase->instance_count)
    {
        shader_addline(buffer, "for (int i = 0; i < %u; ++i)\n{\n", phase->instance_count);
        shader_addline(buffer, "hs_%s_phase%u(i);\n", phase_name, phase_idx);
        shader_addline(buffer, "}\n");
    }
    else
    {
        shader_addline(buffer, "hs_%s_phase%u();\n", phase_name, phase_idx);
    }
}