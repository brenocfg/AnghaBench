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
struct wined3d_shader_primitive_type {int type; int patch_vertex_count; } ;

/* Variables and functions */
#define  WINED3D_PT_LINELIST 139 
#define  WINED3D_PT_LINELIST_ADJ 138 
#define  WINED3D_PT_LINESTRIP 137 
#define  WINED3D_PT_LINESTRIP_ADJ 136 
#define  WINED3D_PT_PATCH 135 
#define  WINED3D_PT_POINTLIST 134 
#define  WINED3D_PT_TRIANGLEFAN 133 
#define  WINED3D_PT_TRIANGLELIST 132 
#define  WINED3D_PT_TRIANGLELIST_ADJ 131 
#define  WINED3D_PT_TRIANGLESTRIP 130 
#define  WINED3D_PT_TRIANGLESTRIP_ADJ 129 
#define  WINED3D_PT_UNDEFINED 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_primitive_type(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_primitive_type *primitive_type)
{
    switch (primitive_type->type)
    {
        case WINED3D_PT_UNDEFINED:
            shader_addline(buffer, "undefined");
            break;
        case WINED3D_PT_POINTLIST:
            shader_addline(buffer, "pointlist");
            break;
        case WINED3D_PT_LINELIST:
            shader_addline(buffer, "linelist");
            break;
        case WINED3D_PT_LINESTRIP:
            shader_addline(buffer, "linestrip");
            break;
        case WINED3D_PT_TRIANGLELIST:
            shader_addline(buffer, "trianglelist");
            break;
        case WINED3D_PT_TRIANGLESTRIP:
            shader_addline(buffer, "trianglestrip");
            break;
        case WINED3D_PT_TRIANGLEFAN:
            shader_addline(buffer, "trianglefan");
            break;
        case WINED3D_PT_LINELIST_ADJ:
            shader_addline(buffer, "linelist_adj");
            break;
        case WINED3D_PT_LINESTRIP_ADJ:
            shader_addline(buffer, "linestrip_adj");
            break;
        case WINED3D_PT_TRIANGLELIST_ADJ:
            shader_addline(buffer, "trianglelist_adj");
            break;
        case WINED3D_PT_TRIANGLESTRIP_ADJ:
            shader_addline(buffer, "trianglestrip_adj");
            break;
        case WINED3D_PT_PATCH:
            shader_addline(buffer, "patch%u", primitive_type->patch_vertex_count);
            break;
        default:
            shader_addline(buffer, "<unrecognized_primitive_type %#x>", primitive_type->type);
            break;
    }
}