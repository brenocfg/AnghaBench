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
typedef  enum wined3d_primitive_type { ____Placeholder_wined3d_primitive_type } wined3d_primitive_type ;
typedef  int GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  GL_LINES 138 
#define  GL_LINES_ADJACENCY_ARB 137 
#define  GL_LINE_STRIP 136 
#define  GL_LINE_STRIP_ADJACENCY_ARB 135 
#define  GL_PATCHES 134 
#define  GL_POINTS 133 
#define  GL_TRIANGLES 132 
#define  GL_TRIANGLES_ADJACENCY_ARB 131 
#define  GL_TRIANGLE_FAN 130 
#define  GL_TRIANGLE_STRIP 129 
#define  GL_TRIANGLE_STRIP_ADJACENCY_ARB 128 
 int WINED3D_PT_LINELIST ; 
 int WINED3D_PT_LINELIST_ADJ ; 
 int WINED3D_PT_LINESTRIP ; 
 int WINED3D_PT_LINESTRIP_ADJ ; 
 int WINED3D_PT_PATCH ; 
 int WINED3D_PT_POINTLIST ; 
 int WINED3D_PT_TRIANGLEFAN ; 
 int WINED3D_PT_TRIANGLELIST ; 
 int WINED3D_PT_TRIANGLELIST_ADJ ; 
 int WINED3D_PT_TRIANGLESTRIP ; 
 int WINED3D_PT_TRIANGLESTRIP_ADJ ; 
 int WINED3D_PT_UNDEFINED ; 
 int /*<<< orphan*/  debug_d3dprimitivetype (int) ; 

__attribute__((used)) static enum wined3d_primitive_type d3d_primitive_type_from_gl(GLenum primitive_type)
{
    switch (primitive_type)
    {
        case GL_POINTS:
            return WINED3D_PT_POINTLIST;

        case GL_LINES:
            return WINED3D_PT_LINELIST;

        case GL_LINE_STRIP:
            return WINED3D_PT_LINESTRIP;

        case GL_TRIANGLES:
            return WINED3D_PT_TRIANGLELIST;

        case GL_TRIANGLE_STRIP:
            return WINED3D_PT_TRIANGLESTRIP;

        case GL_TRIANGLE_FAN:
            return WINED3D_PT_TRIANGLEFAN;

        case GL_LINES_ADJACENCY_ARB:
            return WINED3D_PT_LINELIST_ADJ;

        case GL_LINE_STRIP_ADJACENCY_ARB:
            return WINED3D_PT_LINESTRIP_ADJ;

        case GL_TRIANGLES_ADJACENCY_ARB:
            return WINED3D_PT_TRIANGLELIST_ADJ;

        case GL_TRIANGLE_STRIP_ADJACENCY_ARB:
            return WINED3D_PT_TRIANGLESTRIP_ADJ;

        case GL_PATCHES:
            return WINED3D_PT_PATCH;

        default:
            FIXME("Unhandled primitive type %s.\n", debug_d3dprimitivetype(primitive_type));
        case ~0u:
            return WINED3D_PT_UNDEFINED;
    }
}