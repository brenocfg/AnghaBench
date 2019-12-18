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

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*) ; 

__attribute__((used)) static void shader_glsl_fixup_position(struct wined3d_string_buffer *buffer)
{
    /* Write the final position.
     *
     * OpenGL coordinates specify the center of the pixel while D3D coords
     * specify the corner. The offsets are stored in z and w in
     * pos_fixup. pos_fixup.y contains 1.0 or -1.0 to turn the rendering
     * upside down for offscreen rendering. pos_fixup.x contains 1.0 to allow
     * a MAD. */
    shader_addline(buffer, "gl_Position.y = gl_Position.y * pos_fixup.y;\n");
    shader_addline(buffer, "gl_Position.xy += pos_fixup.zw * gl_Position.ww;\n");

    /* Z coord [0;1]->[-1;1] mapping, see comment in get_projection_matrix()
     * in utils.c
     *
     * Basically we want (in homogeneous coordinates) z = z * 2 - 1. However,
     * shaders are run before the homogeneous divide, so we have to take the w
     * into account: z = ((z / w) * 2 - 1) * w, which is the same as
     * z = z * 2 - w. */
    shader_addline(buffer, "gl_Position.z = gl_Position.z * 2.0 - gl_Position.w;\n");
}