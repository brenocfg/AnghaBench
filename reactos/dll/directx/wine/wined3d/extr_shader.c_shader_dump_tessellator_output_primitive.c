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
typedef  enum wined3d_tessellator_output_primitive { ____Placeholder_wined3d_tessellator_output_primitive } wined3d_tessellator_output_primitive ;

/* Variables and functions */
#define  WINED3D_TESSELLATOR_OUTPUT_LINE 131 
#define  WINED3D_TESSELLATOR_OUTPUT_POINT 130 
#define  WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW 129 
#define  WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CW 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_tessellator_output_primitive(struct wined3d_string_buffer *buffer,
        enum wined3d_tessellator_output_primitive output_primitive)
{
    switch (output_primitive)
    {
        case WINED3D_TESSELLATOR_OUTPUT_POINT:
            shader_addline(buffer, "point");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_LINE:
            shader_addline(buffer, "line");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CW:
            shader_addline(buffer, "triangle_cw");
            break;
        case WINED3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW:
            shader_addline(buffer, "triangle_ccw");
            break;
        default:
            shader_addline(buffer, "unknown_tessellator_output_primitive(%#x)", output_primitive);
            break;
    }
}